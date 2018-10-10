using System;
using Server;
using System.Net;

namespace ConsoleServer {
	class ServerConsole {
		static void Main(string[] args) {
			Console.WriteLine("Starting programm...");
			Console.Title = "Chat: Server";

			Server.Server server = new Server.Server();
			Console.CancelKeyPress += (a, b) => server.StopServer();

			string ip, tmp = null;
			ushort port;

			while (true) {
				Console.Write("Input ip, or [Enter] for {0}: ", Server.Server.defaultIp);
				tmp = Console.ReadLine();
				if(tmp.Length == 0)
					tmp = Server.Server.defaultIp;
				if (!IPAddress.TryParse(tmp, out IPAddress tmpIp)) {
					ConsoleColor prev = Console.ForegroundColor;
					Console.ForegroundColor = ConsoleColor.Red;
					Console.WriteLine("Error: Cant parse ip!");
					Console.ForegroundColor = prev;
				}
				else
					break;
			}
			ip = tmp;

			while (true) {
				Console.Write("Input port, or [Enter] for {0}: ", Server.Server.defaultPort);
				tmp = Console.ReadLine();
				if (tmp.Length == 0)
					tmp = Server.Server.defaultPort.ToString();
				if (!ushort.TryParse(tmp, out port)) {
					ConsoleColor prev = Console.ForegroundColor;
					Console.ForegroundColor = ConsoleColor.Red;
					Console.WriteLine("Error: Wrong port!");
					Console.ForegroundColor = prev;
				}
				else
					break;
			}

			Console.WriteLine("Setting Connection...");
			server.SetConnection(ip, port);
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
					server.SendEveryoneMessage("Server shutdown!");
					isRunning = false;
				}
			}

			server.StopServer();
		}
	}
}
