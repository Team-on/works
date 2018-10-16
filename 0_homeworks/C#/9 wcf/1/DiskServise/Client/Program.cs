using System;
using System.IO;

using System.ServiceModel;
using DiskServise;

namespace Client {
	class Program {
		static void Main(string[] args) {
			ChannelFactory<IDiskServise> factory = new ChannelFactory<IDiskServise>(new BasicHttpBinding(),
				new EndpointAddress("http://localhost:8733/Design_Time_Addresses/DiskServiseDll/DiskServise/")
			);

			IDiskServise channel = factory.CreateChannel();

			Console.Write("Input path: ");
			string[] result = channel.GetDiskInfo(Console.ReadLine());

			foreach (var i in result) {
				if(Path.GetExtension(i) == "")
					Console.Write("Directory\t");
				else
					Console.Write("File\t");
				Console.WriteLine(i);
			}

			Console.ReadLine();
			factory.Close();
		}
	}
}
