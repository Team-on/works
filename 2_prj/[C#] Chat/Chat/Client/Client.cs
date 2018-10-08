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

		public bool IsRecieve() {
			return stream.DataAvailable;
		}

		public byte[] Recieve() {
			return MyProtocol.Protocol.Recieve(stream);
		}

		public void Send(string message) {
			MyProtocol.Protocol.Send(stream, message);
		}

		public void Send(byte[] data) {
			MyProtocol.Protocol.Send(stream, data);
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
