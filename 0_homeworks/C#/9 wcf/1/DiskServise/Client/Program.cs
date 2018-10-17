using System;
using System.IO;

using System.ServiceModel;

namespace Client {
	class Program {
		static void Main(string[] args) {
			using (DiskServiseLink.DiskServiseClient cl = new DiskServiseLink.DiskServiseClient()) {
				Console.Write("Input path: ");
				string[] result = cl.GetDiskInfo(Console.ReadLine());

				foreach (var i in result) {
					if (Path.GetExtension(i) == "")
						Console.Write("Directory\t");
					else
						Console.Write("File\t");
					Console.WriteLine(i);
				}

			}
			Console.ReadLine();
		}
	}
}
