using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server {
	class Program {
		static void Main(string[] args) {
			Server server = new Server();
			server.SetConnection(port: 63255);
			server.StartServer();

			while (Console.ReadKey().Key != ConsoleKey.Escape)
				System.Threading.Thread.Sleep(100);

			server.StopServer();
		}
	}
}
