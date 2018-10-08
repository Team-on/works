using System;
using Server;

namespace ConsoleServer {
	class Program {
		static void Main(string[] args) {
			Server.Server server = new Server.Server();
			server.SetConnection(port: 63255);
			server.StartServer();

			while (Console.ReadKey().Key != ConsoleKey.Escape)
				System.Threading.Thread.Sleep(100);

			server.StopServer();
		}
	}
}
