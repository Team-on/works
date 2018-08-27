using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Timers;

using System.Net;

using Newtonsoft.Json;

using EzDBAccess;

namespace Phonebook {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		bool IsAdmin = false;

		Lazy<AddWindow> addWindow = new Lazy<AddWindow>();
		Lazy<RemoveWindow> removeWindow = new Lazy<RemoveWindow>();
		Lazy<FindWindow> findWindow = new Lazy<FindWindow>();

		internal EzDBList<PhoneBook> phonebook;

		Random Random { get; set; }
		WebClient Client { get; set; }
		RemoveWindow RemoveWindow => removeWindow.Value;
		AddWindow AddWindow => addWindow.Value;
		FindWindow FindWindow => findWindow.Value;

		static public MainWindow Window { get; set; }

		public MainWindow() {
			InitializeComponent();
			Client = new WebClient();
			Random = new Random();
			ServicePointManager.ServerCertificateValidationCallback = new System.Net.Security.RemoteCertificateValidationCallback(
				delegate { return true; }
			);

			phonebook = new EzDBList<PhoneBook>("System.Data.SqlClient", @"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True", false);

			ushort MaxUsers = 1000;
			if(phonebook.Count() < MaxUsers / 2) {
				try {
					Stream data = Client.OpenRead($"https://randomuser.me/api/?nat=us&inc=gender,name,location,phone&results={MaxUsers}");
					StreamReader reader = new StreamReader(data);
					dynamic human = JsonConvert.DeserializeObject(reader.ReadToEnd());
					data.Close();
					reader.Close();

					for(ushort i = 0; i < MaxUsers; ++i) {
						string[] loc = human.results[i].location.street.ToString().Split(' ');
						string street = "";
						for(byte j = 1; j < loc.Length; ++j)
							street += loc[j] + ' ';
						street.TrimEnd();

						phonebook.Add(new PhoneBook(
							MakeFirstUpper(human.results[i].name.first.ToString()),
							MakeFirstUpper(human.results[i].name.last.ToString()),
							human.results[i].phone.ToString(),
							MakeFirstUpper(human.results[i].location.city.ToString()),
							MakeAllUpper(street),
							int.Parse(loc[0]),
							Random.Next(1, 101)
						));
					}
				}
				catch(Exception ex) {
					MessageBox.Show("Cant download random humans from randomuser.me\nCheck your internet connection", "Error!", MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK);
					MessageBox.Show(ex.Message + "\n\n" + ex.Source + "\n\n" + ex.StackTrace, "Error!", MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK);
				}
			}

			dataGrid.ItemsSource = phonebook;
			dataGrid.Items.Refresh();
			Window = this;
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {

		}

		private void AddBtn_Click(object sender, RoutedEventArgs e) {
			AddWindow.ShowDialog();
			dataGrid.Items.Refresh();
		}

		private void RemoveBtn_Click(object sender, RoutedEventArgs e) {
			RemoveWindow.ShowDialog();
			dataGrid.Items.Refresh();
		}

		private void FindBtn_Click(object sender, RoutedEventArgs e) {
			FindWindow.ShowDialog();
		}

		private void AddRandomBtn_Click(object sender, RoutedEventArgs e) {
			Stream data = Client.OpenRead("https://randomuser.me/api/?nat=us&inc=gender,name,location,phone");
			StreamReader reader = new StreamReader(data);

			dynamic human = JsonConvert.DeserializeObject(reader.ReadToEnd());
			string[] loc = human.results[0].location.street.ToString().Split(' ');
			string street = "";
			for(byte i = 1; i < loc.Length; ++i)
				street += loc[i] + ' ';
			street.TrimEnd();

			phonebook.Add(new PhoneBook(
				MakeFirstUpper(human.results[0].name.first.ToString()),
				MakeFirstUpper(human.results[0].name.last.ToString()),
				human.results[0].phone.ToString(),
				MakeFirstUpper(human.results[0].location.city.ToString()),
				MakeAllUpper(street),
				int.Parse(loc[0]),
				Random.Next(1, 101)
			));

			data.Close();
			reader.Close();

			dataGrid.Items.Refresh();
		}

		private void LoginBtn_Click(object sender, RoutedEventArgs e) {
			IsAdmin = !IsAdmin;

			if(IsAdmin)
				LoginBtn.Content = "Logout";
			else
				LoginBtn.Content = "Login";

			foreach(UIElement c in stackPanel.Children)
				if(c is Button b && b != LoginBtn)
					c.IsEnabled = IsAdmin;
		}

		string MakeFirstUpper(string str) {
			if(str.Length == 0)
				return str;
			if(str.Length == 1)
				return str.ToUpper();
			return char.ToUpper(str[0]) + str.Substring(1);
		}

		string MakeAllUpper(string str) {
			string rez = "";
			foreach(var s in str.Split(' '))
				rez += MakeFirstUpper(s) + ' ';
			rez.TrimEnd();
			return rez;
		}

		private void Window_Closed(object sender, EventArgs e) {

		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
			if(addWindow.IsValueCreated)
				addWindow.Value.Close();
			if(removeWindow.IsValueCreated)
				removeWindow.Value.Close();
			if(findWindow.IsValueCreated)
				findWindow.Value.Close();
		}
	}
}
