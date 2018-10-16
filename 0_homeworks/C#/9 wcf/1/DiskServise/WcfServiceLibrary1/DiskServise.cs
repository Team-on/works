using System.Collections.Generic;
using System.IO;

namespace DiskServise {
	public class DiskServise : IDiskServise {
		public string[] GetDiskInfo(string path) {
			if (!Directory.Exists(path)) 
				return null;

			List<string> rez = new List<string>();

			foreach (var dir in Directory.EnumerateDirectories(path))
				rez.Add(Path.GetDirectoryName(dir));

			foreach (var file in Directory.EnumerateFiles(path))
				rez.Add(Path.GetFileName(file));

			return rez.ToArray();
		}
	}
}
