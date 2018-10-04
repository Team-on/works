using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ClientLib;

namespace ConsoleClient {
	class ClientConsole {
		static bool isRunning = true;

		static void Main(string[] args) {
			User user = new User("Console user", ConsoleColor.White);

			Client client = new Client();
			Console.CancelKeyPress += (a, b) => client.Dispose();
			client.SetUser(user);
			client.SetConnection("127.0.0.1", 63255);

			client.Send("Hi, its me - " + user.Name);

			string message = "";
			while (isRunning) {
				if (client.IsRecieve())
					Console.WriteLine(client.Recieve());
				if (Console.KeyAvailable) {
					ConsoleKeyInfo key = Console.ReadKey();
					if (key.Key == ConsoleKey.Escape)
						isRunning = false;
					else if(key.Key != ConsoleKey.Enter){
						message += key.KeyChar;
					}
					else
						client.Send(message);
				}
			}

			client.Dispose();
		}
	}
}
