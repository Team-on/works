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

using EzDBAccess;

namespace Phonebook {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		EzDBList<PhoneBook> phonebook;
		PhoneBook currPhone;

		public MainWindow() {
			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			phonebook = new EzDBList<PhoneBook>("System.Data.SqlClient", @"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True", false);
			currPhone = new PhoneBook();
			dataGrid.ItemsSource = phonebook;
		}

		private void AddBtn_Click(object sender, RoutedEventArgs e) {
			phonebook.Add(new PhoneBook("123", "c", "s", "n", "h"));
			dataGrid.Items.Refresh();
		}

		private void RemoveBtn_Click(object sender, RoutedEventArgs e) {

		}
	}
}
