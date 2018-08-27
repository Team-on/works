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
	/// Interaction logic for LoginWindow.xaml
	/// </summary>
	public partial class LoginWindow : Window {
		public LoginWindow() {
			InitializeComponent();
		}

		private void backBtn_Click(object sender, RoutedEventArgs e) {
			this.Hide();
		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
			if(this.IsActive) {
				e.Cancel = true;
				this.Hide();
			}
		}

		private void LoginBtn_Click(object sender, RoutedEventArgs e) {

		}
	}
}
