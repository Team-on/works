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
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Data;
using System.Data.Entity;

namespace WpfApp1 {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		public MainWindow() {
			Database.SetInitializer<VacancyContext>(new DropCreateDatabaseIfModelChanges<VacancyContext>());
			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			Parser parser = new Parser();
			parser.Parse(".NET", "", "");
		}
	}
}
