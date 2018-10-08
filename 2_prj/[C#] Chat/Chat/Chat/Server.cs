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
			foreach (var user in users) {
				user.thread.Abort();
				user.stream.Dispose();
				user.client.Dispose();
			}
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

			CommandType command = Recieve(stream, out byte[] data);
			if (command != CommandType.Connect)
				return;

			var currUser = new ServerSideUser() {
				user = ClientLib.User.Deserialize(data),
				client = client,
				stream = stream,
				thread = Thread.CurrentThread
			};
			users.Add(currUser);
			SendAll(null, currUser.user.Name + " connected!");

			bool isRunning = true;
			do {
				while (!stream.CanRead)
					Thread.Sleep(100);

				command = Recieve(stream, out data);

				switch (command) {
					case CommandType.None:
						break;
					case CommandType.Exit:
						SendAll(null, currUser.user.Name + " has left!");
						isRunning = false;
						break;
					case CommandType.String:
						SendAll(null, currUser.user.Name + ": " + Encoding.UTF8.GetString(data, 0, data.Length));
						break;
					case CommandType.RawData:
						break;
					default:
						break;
				}
			} while (isRunning);

			users.Remove(currUser);
			stream.Close();
			client.Close();
		}

		public CommandType Recieve(NetworkStream stream, out byte[] data) {
			return Protocol.Recieve(stream, out data); 
		}

		public void Send(NetworkStream stream, string message) {
			MyProtocol.Protocol.SendString(stream, message);
		}

		public void Send(NetworkStream stream, byte[] data) {
			MyProtocol.Protocol.SendRawData(stream, data);
		}

		public void SendAll(ServerSideUser sender, string message) {
			foreach (var user in users) {
				Send(user.stream, message);
			}
		}
	}
}
