using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

using ClientLib;
using MyProtocol;

namespace ConsoleClient {
	class ClientConsole {
		static bool isRunning = true;

		static void Main(string[] args) {
			Console.WriteLine("Starting programm...");
			Console.Title = "Chat";

			Client client = new Client();
			Console.CancelKeyPress += (a, b) => client.Dispose();

			string ip, tmp = null;
			ushort port;

			while (true) {
				Console.Write("Input ip, or [Enter] for {0}: ", Client.defaultIp);
				tmp = Console.ReadLine();
				if (tmp.Length == 0)
					tmp = Client.defaultIp;
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
				Console.Write("Input port, or [Enter] for {0}: ", Client.defaultPort);
				tmp = Console.ReadLine();
				if (tmp.Length == 0)
					tmp = Client.defaultPort.ToString();
				if (!ushort.TryParse(tmp, out port)) {
					ConsoleColor prev = Console.ForegroundColor;
					Console.ForegroundColor = ConsoleColor.Red;
					Console.WriteLine("Error: Wrong port!");
					Console.ForegroundColor = prev;
				}
				else
					break;
			}

			ConsoleColor userColor;
			string userName;

			while (true) {
				userName = "ConsoleUser";
				Console.Write("Input user name, or [Enter] for {0}: ", userName);
				tmp = Console.ReadLine();
				if (tmp.Length == 0)
					tmp = userName;

				ErrorName error = User.IsAllowedName(tmp);
				if (error == ErrorName.None) {
					userName = tmp;
					break;
				}
				else {
					ConsoleColor prev = Console.ForegroundColor;
					Console.ForegroundColor = ConsoleColor.Red;
					Console.WriteLine("Error: {0}", error);
					Console.ForegroundColor = prev;
				}
			}

			while (true) {
				userColor = ConsoleColor.White;
				Console.Write("Input color, or [Enter] for {0}: ", userColor);
				tmp = Console.ReadLine();
				if (tmp.Length == 0)
					tmp = userColor.ToString();

				if (!Enum.TryParse(tmp, out userColor)) {
					ConsoleColor prev = Console.ForegroundColor;
					Console.ForegroundColor = ConsoleColor.Red;
					Console.WriteLine("Error: Color not supported");
					Console.ForegroundColor = prev;
				}
				else {
					ErrorColor error = User.IsAllowedColor(userColor);
					if (error == ErrorColor.None) {
						break;
					}
					else {
						ConsoleColor prev = Console.ForegroundColor;
						Console.ForegroundColor = ConsoleColor.Red;
						Console.WriteLine("Error: {0}", error);
						Console.ForegroundColor = prev;
					}
				}
			}

			User user = new User(userName, userColor);
			client.SetUser(user);


			Console.WriteLine("Setting Connection...");
			client.SetConnection(ip, port);
			Console.WriteLine("Connection established!");
			Console.WriteLine("Type anything and press [Enter] to send message");


			string message = "";
			int x = 0, y = Console.CursorTop;

			while (isRunning) {
				if (Console.CursorLeft != 9 && message == "") {
					Console.SetCursorPosition(0, 0);
					Console.SetCursorPosition(0, Console.WindowHeight - 1);
					Console.Write("Message: ");
				}

				if(client.IsRecieve()) {
					if(y >= Console.WindowHeight - 2) {
						Console.Clear();
						y = 0;
					}
					Console.SetCursorPosition(x, y++);
					RecieveResult result = client.Recieve(out byte[] data);
					if (result == null) {
						isRunning = false;
						continue;
					}

					if (Protocol.IsServerMessage(result.receiverType)) {
						ConsoleColor prev = Console.ForegroundColor;
						Console.ForegroundColor = ConsoleColor.Yellow;
						Console.Write("I got server message" + result.commandType.ToString());
						if (result.commandType == CommandType.String) {
							Console.Write(": ");
							Console.ForegroundColor = ConsoleColor.Red;
							ConsoleWriteMultiline(Encoding.UTF8.GetString(data, 0, data.Length));
						}
						Console.ForegroundColor = prev;
					}
					else if (Protocol.IsClientMessage(result.receiverType)) {
						ConsoleWriteMultiline(result.receiverType.ToString() + ' ' + result.commandType.ToString() + ' ' + Encoding.UTF8.GetString(data, 0, data.Length));
					}
				}

				if (Console.KeyAvailable) {
					Console.CursorVisible = false;
					ConsoleKeyInfo key = Console.ReadKey();
					Console.CursorVisible = true;

					if(key.Key == ConsoleKey.Escape) {
						isRunning = false;
					}
					else if(key.Key == ConsoleKey.Enter) {
						client.Send(message);
						message = "";
						Console.SetCursorPosition(0, Console.WindowHeight - 1);
						Console.Write(new string(' ', Console.WindowWidth));
					}
					else {
						message += key.KeyChar;
					}
				}

			}

			client.Dispose();

			void ConsoleWriteMultiline(string str) {
				if (str != null)
					Console.WriteLine(str);
				y += str.Length / Console.BufferWidth;
			}
		}
	}
}
