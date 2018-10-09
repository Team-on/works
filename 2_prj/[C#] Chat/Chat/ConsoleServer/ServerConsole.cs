using System;
using Server;

namespace ConsoleServer {
	class ServerConsole {
		static void Main(string[] args) {
			Console.WriteLine("Starting programm...");
			Console.Title = "Chat: Server";

			Server.Server server = new Server.Server();
			Console.CancelKeyPress += (a, b) => server.StopServer();
			Console.WriteLine("Setting Connection...");
			server.SetConnection(port: 63255);
			Console.WriteLine("Starting Server...");
			server.StartServer();

			Console.WriteLine("Server started");
			Console.WriteLine("Type \"Send [Message]\" to send smth to all users");
			Console.WriteLine("Type \"Stop\" to kick all users");
			Console.WriteLine("Type \"Exit\" or CTRL+C to shutdown server");

			bool isRunning = true;
			string message, sub;
			string[] split;

			while (isRunning) {
				message = Console.ReadLine();
				split = message.Split(' ');
				sub = split[0].Trim().ToLower();
				if (sub == "send") {
					server.SendEveryoneMessage(message.Replace(split[0], "").Trim());
				}
				else if (sub == "stop") {
					server.SendEveryoneMessage("All kicked!");
					server.SendEveryoneCommand(MyProtocol.CommandType.Exit);
				}
				else if (sub == "exit") {
					server.SendEveryoneMessage("All kicked!");
					isRunning = false;
				}
			}

			server.StopServer();
		}
	}
}
