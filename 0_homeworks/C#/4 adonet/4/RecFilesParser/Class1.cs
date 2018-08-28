using System;
using System.IO;
using System.Xml;
using System.Collections.Generic;

namespace RecFilesParser {
	public class FileFinderSettings {
		string[] usedExt;
		ushort maxFileLength;

		public ushort MaxFileLength => maxFileLength;
		public string[] UsedExt => usedExt;

		public FileFinderSettings() { }

		public FileFinderSettings(string[] ext, ushort maxfilelength) {
			maxFileLength = maxfilelength;
			usedExt = ext;
			FixExt();
		}

		public void ReadFromXml(string path) {
			List<string> tmpExt = new List<string>();

			XmlDocument xml = new XmlDocument();
			xml.Load(path);

			foreach(XmlNode i in xml.ChildNodes[1].ChildNodes) {
				switch(i.Name.ToLower()) {
					case "maxlength":
						ushort.TryParse(i.InnerText, out maxFileLength);
						break;
					case "fileextension":
						tmpExt.Add(i.InnerText);
						break;
				}
			}

			usedExt = tmpExt.ToArray();
			tmpExt.Clear();

			FixExt();
		}

		void FixExt() {
			for(ushort i = 0; i < usedExt.Length; ++i)
				usedExt[i] = usedExt[i].ToLower();
		}

	}

	public class FileFinder {
		LinkedList<FileInfo> filesList;
		FileFinderSettings settings;

		public LinkedList<FileInfo> Files => filesList;

		public FileFinder(FileFinderSettings Settings) {
			filesList = new LinkedList<FileInfo>();
			settings = Settings;
		}

		public void Find() {
			DriveInfo[] drives = DriveInfo.GetDrives();
			foreach(DriveInfo drive in drives)
				if(drive.IsReady)
					RecParse(drive.Name);
		}

		void RecParse(string dirName) {
			if(settings.MaxFileLength != 0 && dirName.Length > settings.MaxFileLength)
				return;

			string[] dirs, files;
			try {
				dirs = Directory.GetDirectories(dirName);
				files = Directory.GetFiles(dirName);
			}
			catch(Exception exception) {
				return;
			}

			bool isFind = false;
			foreach(string currFile in files) {
				isFind = false;
				foreach(var ext in settings.UsedExt) {
					if(currFile.Substring(currFile.LastIndexOf('.') + 1).ToLower() == ext) {
						isFind = true;
						break;
					}
				}
				if(isFind) 
					filesList.AddFirst(new FileInfo(currFile));
			}

			foreach(string currDir in dirs)
				RecParse(currDir);
		}
	}
}