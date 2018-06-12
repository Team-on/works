using System;
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
using System.Windows.Shapes;

namespace reminder {
	/// <summary>
	/// Interaction logic for TaskHappen.xaml
	/// </summary>
	public partial class TaskHappen : Window {
		public TaskHappen() {
			InitializeComponent();
			this.Loaded += TaskHappen_Loaded;
		}

		private void TaskHappen_Loaded(object sender, RoutedEventArgs e) {
			Task t = this.Tag as Task;
			this.name.Content = t.name;
			this.theme.Content = t.theme;
			this.descr.Content = t.description;
			this.time.Content = "Time comes! (" + t.dateTime.ToShortDateString() + ' ' + t.dateTime.ToShortTimeString() + ')';
			grid.Children.Add(new Image() { Source = t.image.Source});
			grid.Children.Remove(stackPanel);
			grid.Children.Add(stackPanel);
		}
	}
}
