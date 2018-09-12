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
				Header = "ProcessName",
				Binding = new Binding("ProcessName"),
			});

		}


		private void Window_Loaded(object sender, RoutedEventArgs e) {
			foreach(var p in Process.GetProcesses()) 
				pr.Add(p);
			dataGrid.Items.Refresh();
		}
	}
}
