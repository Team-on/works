using System;
using System.Collections.Generic;
using System.Threading;
using System.Text;
using System.Net;
using System.Net.Sockets;
using MyProtocol;

namespace Server {
	public class Server {
		string ip;
		ushort port;

		TcpListener server;
		Thread serverThread;
		List<ServerSideUser> users = new List<ServerSideUser>();

		public Server() {
			ip = "127.0.0.1";
			port = 63255;
		}

		public void SetConnection(string ip = "127.0.0.1", ushort port = 63255) {
			this.ip = ip;
			this.port = port;

			server = new TcpListener(IPAddress.Parse(ip), port);
			users = new List<ServerSideUser>();
		}

		public void StartServer() {
			server.Start();

			serverThread = new Thread(ProcessServer);
			serverThread.Start();
		}

		public void StopServer() {
			server.Stop();
			serverThread.Abort();
			SendEveryoneCommand(CommandType.Abort);
			foreach (var user in users) {
				user.thread.Abort();
				user.stream.Dispose();
				user.client.Dispose();
			}
		}

		public void SendEveryoneMessage(string message) {
			foreach (var user in users)
				Send(user.stream, ReceiverType.Server_Everyone, message);
		}

		public void SendEveryoneCommand(CommandType commandType) {
			foreach (var user in users)
				Send(user.stream, ReceiverType.Server_Everyone, commandType);
		}

		void ProcessServer() {
			while (true) {
				TcpClient client = server.AcceptTcpClient();
				Thread clientThread = new Thread(new ParameterizedThreadStart(ProcessClient));
				clientThread.Start(client);
			}
		}

		void ProcessClient(object o) {
			TcpClient client = o as TcpClient;
			if (client is null)
				return;
			NetworkStream stream = client.GetStream();

			byte[] data;
			RecieveResult res;


			ServerSideUser currUser = new ServerSideUser() {
				user = null,
				client = client,
				stream = stream,
				thread = Thread.CurrentThread
			};
			users.Add(currUser);

			bool isRunning = true;
			do {
				while (!stream.CanRead)
					Thread.Sleep(100);

				res = Recieve(stream, out data);

				switch (res.receiverType) {
					case ReceiverType.Client_Server:
						switch (res.commandType) {
							case CommandType.Connect:
								currUser.user = ClientLib.User.Deserialize(data);
								SendEveryone(null, currUser.user.Name + " has connected!");
								break;
							case CommandType.Exit:
								isRunning = false;
								users.Remove(currUser);
								SendEveryone(null, currUser.user.Name + " has left!");
								break;
						}
						break;

					case ReceiverType.Client_Everyone:
						switch (res.commandType) {
							case CommandType.String:
								SendEveryone(currUser, currUser.user.Name + ": " + Encoding.UTF8.GetString(data, 0, data.Length));
								break;
							case CommandType.RawData:
								break;
						}
						break;

					case ReceiverType.Client_GroupById:
						switch (res.commandType) {
							default:
								break;
						}
						break;
				}

			} while (isRunning);

			users.Remove(currUser);
			stream.Close();
			client.Close();
		}

		public RecieveResult Recieve(NetworkStream stream, out byte[] data) {
			return Protocol.Recieve(stream, out data);
		}

		void Send(NetworkStream stream, ReceiverType receiverType, string message) {
			MyProtocol.Protocol.SendString(stream, receiverType, message);
		}

		void Send(NetworkStream stream, ReceiverType receiverType, byte[] data) {
			MyProtocol.Protocol.SendRawData(stream, receiverType, data);
		}

		void Send(NetworkStream stream, ReceiverType receiverType, CommandType command) {
			MyProtocol.Protocol.SendCommand(stream, receiverType, command);
		}

		void SendEveryone(ServerSideUser sender, string message) {
			foreach (var user in users)
				Send(user.stream, sender == null ? ReceiverType.Server_Everyone : ReceiverType.Client_Everyone, message);
		}
	}
}
