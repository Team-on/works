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

namespace Phonebook {
	/// <summary>
	/// Interaction logic for AddWindow.xaml
	/// </summary>
	public partial class AddWindow : Window {
		PhoneBook phone;

		public AddWindow() {
			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			InitNew();
		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
			if(this.IsActive) {
				e.Cancel = true;
				InitNew();
				this.Hide();
			}
		}

		void InitNew() {
			phone = new PhoneBook() {};
			this.DataContext = phone;
		}

		private void backBtn_Click(object sender, RoutedEventArgs e) {
			this.Hide();
		}

		private void BoxFirstName_KeyDown(object sender, KeyEventArgs e) {
			if(!((Key.A <= e.Key && e.Key <= Key.Z) || e.Key == Key.Space))
				e.Handled = true;
		}

		private void BoxPhone_KeyDown(object sender, KeyEventArgs e) {
			if(!((Key.D0 <= e.Key && e.Key <= Key.D9) || e.Key == Key.Space || e.Key == Key.OemCloseBrackets || e.Key == Key.OemOpenBrackets))
				e.Handled = true;
		}

		private void BoxAdressStreet_KeyDown(object sender, KeyEventArgs e) {
			if(!((Key.A <= e.Key && e.Key <= Key.Z) || e.Key == Key.Space || e.Key == Key.Decimal || e.Key == Key.OemComma))
				e.Handled = true;
		}

		private void SaveBtn_Click(object sender, RoutedEventArgs e) {
			foreach(var i in new TextBox[] {
				BoxAdressCity, BoxAdressHome, BoxAdressStreet, BoxAdressStreetNum, BoxFirstName, BoxSecondName, BoxPhone}) 
				if(i.Text.Length == 0) 
					return;
			MainWindow.Window.phonebook.Add(phone);
			InitNew();
		}
	}
}
