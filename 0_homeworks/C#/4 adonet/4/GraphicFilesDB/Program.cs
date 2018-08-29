using System;
using System.Collections;
using System.Collections.Generic;

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
		AutoConfigurableMenuState menuState;
		List<System.IO.FileInfo> fileInfo;

		public DBMenu() {
		}

		public void Start() {
			Init();
			Loop();
		}

		void Init() {
			menuState = new AutoConfigurableMenuState();

			menuState.AddMenuItem(new MenuItem() { Text = "Parse files" }, () => {
				Action func = new Action(() => {
					FileFinderSettings settings = new FileFinderSettings();
					settings.ReadFromXml(@".\settings.xml");
					FileFinder fileFinder = new FileFinder(settings);
					fileFinder.Find();

					fileInfo = new List<System.IO.FileInfo>();
					foreach(var i in fileFinder.Files)
						fileInfo.Add(i);

					Console.WriteLine("End file parsing!");
				});

				func.BeginInvoke(null, null);

				return menuState;
			});

			menuState.AddMenuItem(new MenuItem() { Text = "Print files" }, () => {
				try {
					foreach(var file in fileInfo)
						Console.WriteLine(file.FullName);
				}
				catch(Exception ex) {
					Console.WriteLine("Error! First you need parse files");
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
