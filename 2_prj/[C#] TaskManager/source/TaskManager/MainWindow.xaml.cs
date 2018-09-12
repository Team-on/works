using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TaskManager {
	public partial class MainWindow : Window {
		List<Process> pr;

		public MainWindow() {
			InitializeComponent();
			pr = new List<Process>();
			dataGrid.ItemsSource = pr;

			dataGrid.Columns.Add(new DataGridTextColumn() {
				Header = "PID",
				Binding = new Binding("Id"),
			});

			dataGrid.Columns.Add(new DataGridTextColumn() {
				Header = "ProcessName",
				Binding = new Binding("ProcessName"),
			});

			dataGrid.Columns.Add(new DataGridTextColumn() {
				Header = "TotalProcessorTime",
				Binding = new Binding("TotalProcessorTime"),
			});

			dataGrid.Columns.Add(new DataGridTextColumn() {
				Header = "UserProcessorTime",
				Binding = new Binding("UserProcessorTime"),
			});


			dataGrid.Columns.Add(new DataGridTextColumn() {
				Header = "Used memory",
				Binding = new Binding("PrivateMemorySize"),
			});
		}


		private void Window_Loaded(object sender, RoutedEventArgs e) {
			foreach(var p in Process.GetProcesses()) 
				pr.Add(p);
			dataGrid.Items.Refresh();

			System.Timers.Timer t = new System.Timers.Timer() {
				AutoReset = true,
				Interval = 1000,
				Enabled = false,
			};
			t.Elapsed += T_Elapsed;
			t.Start();
		}

		private void T_Elapsed(object sender, System.Timers.ElapsedEventArgs e) {
			pr.Clear();
			foreach(var p in Process.GetProcesses()) {
				pr.Add(p);
			}
			dataGrid.Items.Refresh();
		}

		private void dataGrid_MouseDoubleClick(object sender, MouseButtonEventArgs e) {
			if(dataGrid.SelectedItem == null)
				return;

			try {
				Process p = (Process)dataGrid.SelectedItem;

				string arg = $@"/c taskkill /f /pid {p.Id}";
				ProcessStartInfo process = new ProcessStartInfo("cmd") {
					UseShellExecute = true,
					CreateNoWindow = true,
					//Verb = "runas",
					Arguments = arg,
				};
				Process.Start(process);

				//pr.Remove(p);
				//dataGrid.Items.Refresh();
				//p.Kill();
			}
			catch(Exception ex) {
				MessageBox.Show(ex.Message + '\n' + ex.StackTrace);
			}
		}
	}
}
