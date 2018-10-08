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
			Send(User.Serialize(user));
		}

		public void SetUser(User user) {
			this.user = user;
		}

		public void Send(string message) {
			Send(Encoding.UTF8.GetBytes(message));
		}

		public void Send(byte[] data) {
			byte[] intBytes = BitConverter.GetBytes(data.Length);
			stream.Write(intBytes, 0, 4);
			stream.Write(data, 0, data.Length);
		}

		public bool IsRecieve() {
			return stream.DataAvailable;
		}

		public byte[] Recieve() {
			byte[] data = new byte[4];
			stream.Read(data, 0, 4);
			data = new byte[BitConverter.ToInt32(data, 0)];
			stream.Read(data, 0, data.Length);
			return data;
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
