using System;
using System.Collections.Generic;
using System.Threading;
using System.Text;
using System.Net;
using System.Net.Sockets;

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

			var currUser = new ServerSideUser() {
				user = null,
				client = client,
				stream = stream,
				thread = Thread.CurrentThread
			};

			users.Add(currUser);

			Send(stream, "Welcome, User!");

			bool isRunning = true;
			do {
				while (!stream.CanRead)
					Thread.Sleep(100);

				byte[] data = new byte[256];
				StringBuilder response = new StringBuilder();
				do {
					int bytes = stream.Read(data, 0, data.Length);
					response.Append(Encoding.UTF8.GetString(data, 0, bytes));
				}
				while (stream.DataAvailable);

				if (response.ToString().ToLower() == "exit")
					isRunning = false;

				SendAll(currUser, response.ToString());
				Console.WriteLine(response);
			} while (isRunning);

			users.Remove(currUser);
			stream.Close();
			client.Close();
		}

		public void Send(NetworkStream stream, string message) {
			byte[] data = Encoding.UTF8.GetBytes(message);
			stream.Write(data, 0, data.Length);
		}

		public void SendAll(ServerSideUser sender, string message) {
			foreach (var user in users) {
				Send(user.stream, message);
			}
		}
	}
}
