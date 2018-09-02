using System;
using RecFilesParser;

namespace GraphicFilesDB {
	class Program {
		static void Main(string[] args) {
			//Налаштування також можна передати в конструктор.
			//Якщо maxLength == 0, то довжина не обмежується
			//fileExtension зчитуються незалежно від регістру.
			FileFinderSettings settings = new FileFinderSettings();
			settings.ReadFromXml(@".\settingsExample.xml");

			FileFinder fileFinder = new FileFinder(settings);
			fileFinder.Find();

			foreach(var file in fileFinder.Files)
				Console.WriteLine(file.FullName);
		}
	}
}
