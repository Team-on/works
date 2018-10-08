using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace ClientLib {
	public class Client : IDisposable {
		const ushort MAX_MESSAGE_LENGTH = 10000;

		User user;
		string ip;
		ushort port;

		TcpClient client;
		NetworkStream stream;

		public Client() {
			user = new User();
			ip = "127.0.0.1";
			port = 63255;
		}

		public void SetConnection(string ip, ushort port = 63255) {
			this.ip = ip;
			this.port = port;

			client = new TcpClient();
			client.Connect(ip, port);
			stream = client.GetStream();
		}

		public void SetUser(User user) {
			this.user = user;
		}

		public void Send(string message) {
			byte[] data = Encoding.UTF8.GetBytes(message);
			stream.Write(data, 0, data.Length);
		}

		public bool IsRecieve() {
			return stream.DataAvailable;
		}

		public string Recieve() {
			byte[] data = new byte[256];
			StringBuilder response = new StringBuilder();
			do {
				int bytes = stream.Read(data, 0, data.Length);
				response.Append(Encoding.UTF8.GetString(data, 0, bytes));
			}
			while(stream.DataAvailable);

			return response.ToString();
		}


		bool isClosed = false;
		public void Close() {
			if(!isClosed) {
				Send("exit");
				isClosed = true;
				stream?.Close();
				client?.Close();
			}
		}

		public void Dispose() {
			Close();
		}
	}
}
