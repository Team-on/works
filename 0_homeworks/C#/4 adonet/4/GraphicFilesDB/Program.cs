using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

using System.Data;
using System.Data.Common;
using System.Data.SQLite;
using System.Data.SQLite.Linq;
using System.Data.SQLite.Generic;


using ConsoleOOPMenu;
using RecFilesParser;

namespace GraphicFilesDB {
	class TestMenuState : MenuState {
		private Dictionary<int, MenuItem> menus = new Dictionary<int, MenuItem>() {
			{1, new MenuItem(){Text = "Print 10"}},
			{2, new MenuItem(){Text = "Print files"}},
			{3, new MenuItem(){Text = "Exit"}},
		};
		protected override Dictionary<int, MenuItem> Menus => menus;

		protected override IState NextState(KeyValuePair<int, MenuItem> selectedMenu) {
			if(selectedMenu.Key == 1) {
				Console.WriteLine(10);
			}
			else if(selectedMenu.Key == 2) {
				FileFinderSettings settings = new FileFinderSettings();
				settings.ReadFromXml(@".\settings.xml");

				FileFinder fileFinder = new FileFinder(settings);
				fileFinder.Find();

				foreach(var file in fileFinder.Files)
					Console.WriteLine(file.FullName);
			}
			else if(selectedMenu.Key == 3)
				return null;

			return this;
		}
	}

	class DBMenu {
		const string connectionString = @"Data Source = .\files.db";
		const ConsoleColor attentionColor = ConsoleColor.DarkYellow;
		AutoConfigurableMenuState menuState;

		public DBMenu() {
		}

		public void Start() {
			Init();
			Loop();
		}

		void Init() {
			menuState = new AutoConfigurableMenuState();

			//menuState.AddMenuItem(new MenuItem() { Text = "Create DB" }, () => {
			//	//Вроде і без цього робить
			//	//if(!System.IO.File.Exists(dbName))
			//	//SQLiteConnection.CreateFile(dbName);

			//	//DbProviderFactory factory = DbProviderFactories.GetFactory("System.Data.SQLite");

			//	//DbConnection connection = factory.CreateConnection();
			//	//connection.ConnectionString = connectionString;
			//	//connection.Open();

			//	//DbDataAdapter dataAdapter = factory.CreateDataAdapter();
			//	//dataAdapter.SelectCommand = factory.CreateCommand();
			//	//dataAdapter.SelectCommand.Connection = connection;
			//	//dataAdapter.SelectCommand.CommandText = "select * from file";

			//	//DataSet dataSet = new DataSet("files");
			//	//dataAdapter.Fill(dataSet, "files");


			//	//DataTable table = new DataTable("file");
			//	//DataColumn column = new DataColumn("IdFile", typeof(int)) {
			//	//	AllowDBNull = false,
			//	//	ReadOnly = false,
			//	//	Unique = true,
			//	//	AutoIncrement = true,
			//	//	AutoIncrementSeed = 1,
			//	//	AutoIncrementStep = 1,
			//	//	Caption = "Id file",
			//	//};
			//	//table.Columns.Add(column);

			//	//column = new DataColumn("PathToFile", typeof(string)) {
			//	//	AllowDBNull = false,
			//	//	ReadOnly = false,
			//	//	Caption = "Path to file",
			//	//};
			//	//table.Columns.Add(column);

			//	//column = new DataColumn("FileSize", typeof(ulong)) {
			//	//	AllowDBNull = false,
			//	//	ReadOnly = false,
			//	//	Caption = "File size",
			//	//};
			//	//table.Columns.Add(column);

			//	//dataSet.Tables.Add(table);

			//	//DataRow row = table.NewRow();
			//	//row[1] = "test\\test.jpg";
			//	//row[2] = 666;
			//	//dataSet.Tables[0].Rows.Add(row);
			//	//dataSet.AcceptChanges();

			//	//foreach(DataTable t in dataSet.Tables) {
			//	//	Console.WriteLine($" => {t.TableName}");
			//	//	foreach(DataRow r in t.Rows) {
			//	//		Console.WriteLine($"{r[0]}\t{r[1]}\t{r[2]}");
			//	//	}
			//	//}


			//	////Треба для БД які представлені 1 файлом. Наприклад SQLite
			//	//if(factory is IDisposable disposable)
			//	//	disposable.Dispose();



			//	DataSet dataSet = new DataSet();
			//	dataSet.ReadXml(@".\files.xml");

			//	foreach(DataTable t in dataSet.Tables) {
			//		Console.WriteLine($" => {t.TableName}");
			//		foreach(DataRow r in t.Rows) {
			//			Console.WriteLine($"{r[0]}\t{r[1]}");
			//		}
			//	}

			//	return menuState;
			//});

			menuState.AddMenuItem(new MenuItem() { Text = "Parse, create and fill DB" }, () => {
				FileFinderSettings settings = new FileFinderSettings();
				settings.ReadFromXml(@".\settings.xml");
				FileFinder fileFinder = new FileFinder(settings);

				new MenuItem() { Text = "Start file parsing.\n", TextColor = attentionColor }.Print();
				fileFinder.Find();
				new MenuItem() { Text = "End file parsing.\n", TextColor = attentionColor }.Print();

				new MenuItem() { Text = "Start saving as DB.\n", TextColor = attentionColor }.Print();
				fileFinder.SaveAsXml(@".\files.xml");

				DataSet dataSet = new DataSet();
				dataSet.ReadXml(@".\files.xml");
				new MenuItem() { Text = "End saving as DB.\n", TextColor = attentionColor }.Print();

				foreach(DataTable t in dataSet.Tables) {
					Console.WriteLine($" => {t.TableName}");
					foreach(DataRow r in t.Rows) {
						for(byte i = 0; i < t.Columns.Count; ++i) {
							string str = r[i].ToString();
							if(str.Length > 20)
								str = str.Substring(0, 17) + "...";
							str = str.PadRight(20);
							str += ' ';
							Console.Write(str);
						}
						Console.WriteLine();
					}
				}

				return menuState;
			});



			menuState.AddMenuItem(new MenuItem() { Text = "Exit" }, () => null);
		}

		void Loop() {
			IState startState = menuState;
			while(startState != null)
				startState = startState.RunState();
		}
	}

	class Program {
		static void Main(string[] args) {
			DBMenu menu = new DBMenu();
			menu.Start();
		}
	}
}
