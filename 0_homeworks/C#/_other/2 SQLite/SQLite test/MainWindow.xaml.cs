using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//WPF using
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

//SQL using
using System.Data;
using System.Data.Common;
using System.Data.SQLite;
using System.Data.Entity;

namespace SQLite_test {
	public class ApplicationContext : DbContext {
		public ApplicationContext() : base($"DefaultConnection") { }
		public DbSet<Student> Students { get; set; }
	}

	public partial class MainWindow : Window {
		public const string dbName = @".\university.db";
		ApplicationContext db;
		Student currStudent;

		public MainWindow() {
			InitializeComponent();
			NewCurrStud();
		}

		void NewCurrStud(){
			currStudent = new Student();
			this.DataContext = currStudent;
			IdBox.BorderBrush = FirstNameBox.BorderBrush = SecondNameBox.BorderBrush = SecondNameBox.BorderBrush = Brushes.Gray;
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			CreateBtn.IsEnabled = System.IO.File.Exists(dbName) ? false : true;
			LinkBtn.IsEnabled = !CreateBtn.IsEnabled;
			AddBtn.IsEnabled = false;
			RemoveBtn.IsEnabled = false;
		}

		private void Button_Click(object sender, RoutedEventArgs e) {
			try {
				SQLiteConnection.CreateFile(dbName);

				SQLiteFactory factory = (SQLiteFactory) DbProviderFactories.GetFactory("System.Data.SQLite");
				//using(SQLiteFactory factory = (SQLiteFactory) DbProviderFactories.GetFactory("System.Data.SQLite")) {
				using(SQLiteConnection connection = (SQLiteConnection) factory.CreateConnection()) {
						connection.ConnectionString = $"Data Source = {dbName}";
						connection.Open();

						using(SQLiteCommand command = new SQLiteCommand(connection)) {
							command.CommandText = @"CREATE TABLE Students (
								Id integer PRIMARY KEY AUTOINCREMENT,
								FirstName NVARCHAR(32) NOT NULL,
								SecondName NVARCHAR(32) NOT NULL,
								Course tinyint NOT NULL
							);";
							command.CommandType = CommandType.Text;
							command.ExecuteNonQuery();

							command.CommandText = @"INSERT INTO Students
								(FirstName, SecondName, Course)
								VALUES
								('Dude1', 'Moonlighter', 1),
								('Dude2', 'Grayrat', 1),
								('Dude3', 'Whitehourse', 1),
								('Dude4', 'Nightmarehouse', 2),
								('Dude5', 'Redsocks', 2)
							";
							command.ExecuteNonQuery();

							command.CommandText = @"INSERT INTO Student
								(FirstName, SecondName, Course)
								VALUES
								('Dude1', 'Moonlighter', 1),
								('Dude2', 'Grayrat', 1),
								('Dude3', 'Whitehourse', 1),
								('Dude4', 'Nightmarehouse', 2),
								('Dude5', 'Redsocks', 2)
							";
						}
					}
				//}
			}
			catch(Exception ex) {
				MessageBox.Show(this, ex.Message, ex.Source, MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK);
			}

			CreateBtn.IsEnabled = false;
			LinkBtn.IsEnabled = true;
		}

		private void Button_Click_4(object sender, RoutedEventArgs e) {
			try {
				db = new ApplicationContext();
				db.Students.Load();

				dataGrid.ItemsSource = db.Students.Local;

				if(db.Students.Local.Count == 5) {
					db.Students.Add(new Student("DudeAddedByCode1", "Bluestar", 3));
					db.Students.Add(new Student("DudeAddedByCode2", "Pinkshedule", 3));
					db.Students.Add(new Student("DudeAddedByCode3", "Yellowgrass", 4));
					db.Students.Add(new Student("DudeAddedByCode4", "Whitebeast", 5));
					db.SaveChanges();
				}
			}
			catch(Exception ex) {
				MessageBox.Show(this, ex.Message, ex.Source, MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK);
			}

			LinkBtn.IsEnabled = false;
			AddBtn.IsEnabled = true;
			RemoveBtn.IsEnabled = true;
		}

		private void Button_Click_1(object sender, RoutedEventArgs e) {
			bool errorInValues = false;

			if(currStudent.FirstName.Length > 32 || currStudent.FirstName.Length < 2) { 
				FirstNameBox.BorderBrush = Brushes.Red;
				errorInValues = true;
			}
			else
				FirstNameBox.BorderBrush = Brushes.Gray; 

			if(currStudent.SecondName.Length > 32 || currStudent.FirstName.Length < 2) { 
				SecondNameBox.BorderBrush = Brushes.Red;
				errorInValues = true;
			}
			else
				SecondNameBox.BorderBrush = Brushes.Gray;

			if(currStudent.Course < 1 || currStudent.Course > 6) {
				CourseBox.BorderBrush = Brushes.Red;
				errorInValues = true;
			}
			else
				CourseBox.BorderBrush = Brushes.Gray;

			if(errorInValues)
				return;
			
			db.Students.Add(currStudent);
			db.SaveChanges();
			NewCurrStud();
		}

		private void Button_Click_3(object sender, RoutedEventArgs e) {
			var stud = db.Students.Find(currStudent.Id);
			if(stud != null) {
				db.Students.Remove(stud);
				db.SaveChanges();
				NewCurrStud();
			}
			else
				IdBox.BorderBrush = Brushes.Red;
		}
	}
}
