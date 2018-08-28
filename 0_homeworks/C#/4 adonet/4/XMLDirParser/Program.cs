using System;
using System.IO;
using System.Xml;
using TeamCommander.Output;
using TeamCommander.Support;

namespace XMLDirParser {
	static class DirFileParserOptimized {
		static XmlDocument xml;
		static XmlAttribute attrib;
		static FileInfo finf;

		static public void Parse(string path) {
			xml = new XmlDocument();

			XmlDeclaration decl = xml.CreateXmlDeclaration("1.0", "utf-8", "yes");
			xml.AppendChild(decl);

			XmlElement root = xml.CreateElement("root");

			DriveInfo[] drives = DriveInfo.GetDrives();
			foreach (DriveInfo drive in drives) {
				XmlElement disk = xml.CreateElement("disk");

				attrib = xml.CreateAttribute("driverName");
				attrib.Value = drive.Name;
				disk.Attributes.Append(attrib);

				attrib = xml.CreateAttribute("driveType");
				attrib.Value = drive.DriveType.ToString();
				disk.Attributes.Append(attrib);

				attrib = xml.CreateAttribute("isReady");
				attrib.Value = drive.IsReady.ToString();
				disk.Attributes.Append(attrib);

				if (drive.IsReady) {
					attrib = xml.CreateAttribute("driveFormat");
					attrib.Value = drive.DriveFormat.ToString();
					disk.Attributes.Append(attrib);

					attrib = xml.CreateAttribute("totalSize");
					attrib.Value = drive.TotalSize.ToString();
					disk.Attributes.Append(attrib);

					attrib = xml.CreateAttribute("freeSpace");
					attrib.Value = drive.TotalFreeSpace.ToString();
					disk.Attributes.Append(attrib);

					attrib = xml.CreateAttribute("availableFreeSpace");
					attrib.Value = drive.AvailableFreeSpace.ToString();
					disk.Attributes.Append(attrib);

					GetDirsAndFiles(drive.Name, disk);
				}

				root.AppendChild(disk);
			}

			xml.AppendChild(root);
			xml.Save(path);
		}

		static ulong GetDirsAndFiles(string dirName, XmlElement father) {
            //if (dirName.Length > 10)
            //    return 0;
			string[] dirs, files;
			try {
				dirs = Directory.GetDirectories(dirName);
				files = Directory.GetFiles(dirName);
			}
			catch (Exception exception) {
				attrib = xml.CreateAttribute("protected");
				attrib.Value = "yes";
				father.Attributes.Append(attrib);

				return 0;
			}

			XmlElement currElem;
			ulong sizeCurrDir = 0;
			foreach (string currFile in files) {
				if(currFile.Substring(currFile.LastIndexOf('.') + 1) != "txt")
					continue;

				finf = new FileInfo(currFile);
				currElem = xml.CreateElement("file");

				attrib = xml.CreateAttribute("name");
				attrib.Value = currFile.Substring(currFile.LastIndexOf('\\') + 1);
				currElem.Attributes.Append(attrib);

				attrib = xml.CreateAttribute("size");
				attrib.Value = finf.Length.ToString();
				currElem.Attributes.Append(attrib);

				sizeCurrDir += (ulong)finf.Length;

				father.AppendChild(currElem);
			}

			foreach (string currDir in dirs) {
				currElem = xml.CreateElement("folder");

				attrib = xml.CreateAttribute("name");
				attrib.Value = currDir.Substring(currDir.LastIndexOf('\\') + 1);
				currElem.Attributes.Append(attrib);

				ulong sizeUpperDir = GetDirsAndFiles(currDir, currElem);
				sizeCurrDir += sizeUpperDir;

				attrib = xml.CreateAttribute("size");
				attrib.Value = sizeUpperDir.ToString();
				currElem.Attributes.Append(attrib);

				father.AppendChild(currElem);
			}

			return sizeCurrDir;
		}
	}

	class Program {
		static void Main(string[] args) {
			DateTime start = DateTime.Now;
			DirFileParserOptimized.Parse(@"D:\test.xml");
			Console.WriteLine(DateTime.Now - start);
		}
	}
}