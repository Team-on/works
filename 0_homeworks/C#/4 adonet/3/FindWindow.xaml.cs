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
using System.Text.RegularExpressions;

namespace Phonebook {
	/// <summary>
	/// Interaction logic for FindWindow.xaml
	/// </summary>
	public partial class FindWindow : Window {
		List<PhoneBook> rezults;
		public FindWindow() {
			InitializeComponent();
			rezults = new List<PhoneBook>();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			dataGrid.ItemsSource = rezults;
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

		private void FindBtn_Click(object sender, RoutedEventArgs e) {
			bool useid = int.TryParse(BoxId.Text, out int id);
			bool usefn = BoxFirstName.Text.Length != 0;
			bool usesn = BoxSecondName.Text.Length != 0;
			bool useph = BoxPhone.Text.Length != 0;
			bool usect = BoxAdressCity.Text.Length != 0;
			bool usestr = BoxAdressStreet.Text.Length != 0;
			bool usestrnum = int.TryParse(BoxAdressStreetNum.Text, out int strnum);
			bool usehm = int.TryParse(BoxAdressHome.Text, out int hm);

			BoxFirstName.Text = BoxFirstName.Text.Trim();
			BoxSecondName.Text = BoxSecondName.Text.Trim();
			BoxPhone.Text = BoxPhone.Text.Trim();
			BoxAdressCity.Text = BoxAdressCity.Text.Trim();
			BoxAdressStreet.Text = BoxAdressStreet.Text.Trim();


			rezults.Clear();

			var query = from a in MainWindow.Window.phonebook
						where (!useid || (useid && a.Id == id)) &&
							  (!usefn || (usefn && Regex.Match(a.FirstName, BoxFirstName.Text).Success)) &&
							  (!usesn || (usesn && Regex.Match(a.LastName, BoxSecondName.Text).Success)) &&
							  (!useph || (useph && Regex.Match(a.Phone, BoxPhone.Text).Success)) &&
							  (!usect || (usect && Regex.Match(a.AdressCity, BoxAdressCity.Text).Success)) &&
							  (!usestr || (usestr && Regex.Match(a.AdressStreet, BoxAdressStreet.Text).Success)) &&
							  (!usestrnum || (usestrnum && a.AdressStreetNum == strnum)) &&
							  (!usehm || (usehm && a.AdressHome == hm))
						select a;
			rezults.AddRange(query);

			/*
			  rezults.AddRange(MainWindow.Window.phonebook.FindAll((a) => {
				bool rez = true;

				if(rez && useid)
					rez = a.Id == id;

				if(rez && usefn)
					rez = Regex.Match(a.FirstName, BoxFirstName.Text).Success;

				if(rez && usesn)
					rez = Regex.Match(a.LastName, BoxSecondName.Text).Success;

				if(rez && useph)
					rez = Regex.Match(a.Phone, BoxPhone.Text).Success;

				if(rez && usect)
					rez = Regex.Match(a.AdressCity, BoxAdressCity.Text).Success;

				if(rez && usestr)
					rez = Regex.Match(a.AdressStreet, BoxAdressStreet.Text).Success;

				if(rez && usestrnum)
					rez = a.AdressStreetNum == strnum;

				if(rez && usehm)
					rez = a.AdressHome == hm;

				return rez;
			}));
			*/

			dataGrid.Items.Refresh();
		}
	}
}
