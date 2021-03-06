﻿using System;
using System.IO;
using System.Xml;
using System.Collections.Generic;

namespace RecFilesParser {
	public class FileFinderSettings {
		List<string> usedExt;
		ushort maxFileLength;

		public ushort MaxFileLength => maxFileLength;
		public List<string> UsedExt => usedExt;

		public FileFinderSettings() { }

		public FileFinderSettings(string[] ext, ushort maxfilelength) {
			maxFileLength = maxfilelength;
			usedExt = new List<string>(ext);
			FixExt();
		}

		public void ReadFromXml(string path) {
			XmlDocument xml = new XmlDocument();
			xml.Load(path);

			usedExt = new List<string>(xml.ChildNodes[1].ChildNodes.Count - 1);

			foreach(XmlNode i in xml.ChildNodes[1].ChildNodes) {
				switch(i.Name.ToLower()) {
					case "maxlength":
						ushort.TryParse(i.InnerText, out maxFileLength);
						break;
					case "fileextension":
						usedExt.Add(i.InnerText);
						break;
				}
			}

			FixExt();
		}

		public void SaveToXml(string path) {
			FixExt();

			XmlDocument xml = new XmlDocument();
			XmlDeclaration decl = xml.CreateXmlDeclaration("1.0", "utf-8", "yes");
			xml.AppendChild(decl);
			XmlElement root = xml.CreateElement("settings");

			XmlElement currElem = xml.CreateElement("maxLength");
			currElem.InnerText = MaxFileLength.ToString();
			root.AppendChild(currElem);

			foreach(var ext in UsedExt) {
				currElem = xml.CreateElement("fileExtension");
				currElem.InnerText = ext;
				root.AppendChild(currElem);
			}

			xml.AppendChild(root);
			xml.Save(path);
		}

		void FixExt() {
			for(ushort i = 0; i < usedExt.Count; ++i)
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

		public void SaveAsXml(string path) {
			XmlDocument xml = new XmlDocument();
			XmlDeclaration decl = xml.CreateXmlDeclaration("1.0", "utf-8", "yes");
			xml.AppendChild(decl);
			XmlElement root = xml.CreateElement("files");

			XmlElement fileElem;
			XmlAttribute attrib;
			foreach(var file in Files) {
				fileElem = xml.CreateElement("file");

				attrib = xml.CreateAttribute("path");
				attrib.Value = file.FullName;
				fileElem.Attributes.Append(attrib);

				attrib = xml.CreateAttribute("size");
				attrib.Value = file.Length.ToString();
				fileElem.Attributes.Append(attrib);

				root.AppendChild(fileElem);
			}

			xml.AppendChild(root);
			xml.Save(path);
		}
	}
}