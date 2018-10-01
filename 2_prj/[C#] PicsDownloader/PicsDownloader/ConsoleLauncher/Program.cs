using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Lib;

namespace ConsoleLauncher {
	class Program {
		static void Main(string[] args) {
			Downloader downloader = new Downloader();
			downloader.Download();
		}
	}
}
