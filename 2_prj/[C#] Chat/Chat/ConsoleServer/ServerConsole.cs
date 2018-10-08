using System;
using Server;

namespace ConsoleServer {
	class ServerConsole {
		static void Main(string[] args) {
			Console.Title = "Chat: Server";

			Server.Server server = new Server.Server();
			Console.CancelKeyPress += (a, b) => server.StopServer();
			server.SetConnection(port: 63255);
			server.StartServer();

			while (Console.ReadKey().Key != ConsoleKey.Escape)
				System.Threading.Thread.Sleep(100);

			server.StopServer();
		}
	}
}
