using System;

using ConsoleOOPMenu;
using RecFilesParser;

namespace GraphicFilesDB {
	class Program {
		static void Main(string[] args) {
			FileFinderSettings settings = new FileFinderSettings();
			settings.ReadFromXml(@".\settings.xml");

			FileFinder fileFinder = new FileFinder(settings);
			fileFinder.Find();


			new Test().Print();
			foreach(var file in fileFinder.Files) {
				Console.WriteLine(file.FullName);
			} 
		}
	}
}
