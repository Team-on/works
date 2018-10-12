using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace TicTacToe {
	class Program {
		static void Main(string[] args) {
			Server server = new Server();

			Console.CancelKeyPress += (a, b) => server.StopServer();

			Console.Title = Dns.GetHostByName(Dns.GetHostName()).AddressList[0].ToString();
			server.SetConnection(/*Console.Title, 63100 */);
			server.StartServer();

			bool isRunning = true;
			do {
				var key = Console.ReadKey();
				if(key.Key == ConsoleKey.Escape)
					isRunning = false;
			} while(isRunning);

			server.StopServer();
		}
	}
}
