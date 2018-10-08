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

			byte[] dataUser = Recieve(stream);

			var currUser = new ServerSideUser() {
				user = ClientLib.User.Deserialize(dataUser),
				client = client,
				stream = stream,
				thread = Thread.CurrentThread
			};

			users.Add(currUser);

			bool isRunning = true;
			StringBuilder response = new StringBuilder();
			do {
				while (!stream.CanRead)
					Thread.Sleep(100);

				byte[] data = Recieve(stream);

				response.Clear();
				response.Append(Encoding.UTF8.GetString(data, 0, data.Length));

				if (response.ToString().ToLower() == "exit")
					isRunning = false;

				SendAll(currUser, response.ToString());
				Console.WriteLine(response);
			} while (isRunning);

			users.Remove(currUser);
			stream.Close();
			client.Close();
		}

		public byte[] Recieve(NetworkStream stream) {
			return MyProtocol.Protocol.Recieve(stream);
		}

		public void Send(NetworkStream stream, string message) {
			MyProtocol.Protocol.Send(stream, message);
		}

		public void Send(NetworkStream stream, byte[] data) {
			MyProtocol.Protocol.Send(stream, data);
		}

		public void SendAll(ServerSideUser sender, string message) {
			foreach (var user in users) {
				Send(user.stream, message);
			}
		}
	}
}
