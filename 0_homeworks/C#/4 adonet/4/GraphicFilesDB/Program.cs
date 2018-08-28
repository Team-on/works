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

	class Program {
		static void Main(string[] args) {
			IState startState = new TestMenuState();
			while(startState != null)
				startState = startState.RunState();
		}
	}
}
