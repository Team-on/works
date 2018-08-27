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
	/// Interaction logic for RemoveWindow.xaml
	/// </summary>
	public partial class RemoveWindow : Window {
		public RemoveWindow() {
			InitializeComponent();
		}

		private void backBtn_Click(object sender, RoutedEventArgs e) {
			this.Hide();
		}

		private void delBtn_Click(object sender, RoutedEventArgs e) {
			bool showError = false;
			if(int.TryParse(IdTextBox.Text, out int Id)) {
				var find = MainWindow.Window.phonebook.Find((a) => a.Id == Id);
				if(find != null)
					MainWindow.Window.phonebook.Remove(find);
				else
					showError = true;
			}
			else
				showError = true;

			if(showError) 
				ShowIdError();
		}

		void ShowIdError() {
			MessageBox.Show(this, "Cant find record with this Id", "Error", MessageBoxButton.OK, MessageBoxImage.Asterisk, MessageBoxResult.OK);
		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
			if(this.IsActive) {
				e.Cancel = true;
				this.Hide();
			}
		}

		private void IdTextBox_KeyDown(object sender, KeyEventArgs e) {
			if(e.Key < Key.D0 || e.Key > Key.D9) 
				e.Handled = true;
		}
	}
}
