using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ClientLib;
using MyProtocol;

namespace ConsoleClient {
	class ClientConsole {
		static bool isRunning = true;

		static void Main(string[] args) {
			Console.Title = "Chat";

			User user = new User("ConsoleUser", ConsoleColor.White);

			Client client = new Client();
			Console.CancelKeyPress += (a, b) => client.Dispose();
			client.SetUser(user);
			client.SetConnection("127.0.0.1", 63255);

			string message = "";
			int x = 0, y = 0;

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
