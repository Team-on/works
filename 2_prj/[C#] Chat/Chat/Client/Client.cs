using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using MyProtocol;

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
			Protocol.SendCommand(stream, ReceiverType.Client_Server, CommandType.Connect, User.Serialize(user));
		}

		public void SetUser(User user) {
			this.user = user;
		}

		public bool IsRecieve() {
			return stream.CanRead && stream.DataAvailable;
		}

		public RecieveResult Recieve(out byte[] data) {
			var res = Protocol.Recieve(stream, out data);
			if (Protocol.IsServerMessage(res.receiverType)) {
				switch (res.commandType) {
					case CommandType.Exit:
						Close();
						return null;
					case CommandType.String:
						break;
					case CommandType.RawData:
						break;
				}
			}
			return res;
		}

		public void Send(string message) {
			MyProtocol.Protocol.SendString(stream, ReceiverType.Client_Everyone, message);
		}

		public void Send(byte[] data) {
			MyProtocol.Protocol.SendRawData(stream, ReceiverType.Client_Everyone, data);
		}

		bool isClosed = false;
		public void Close() {
			if(!isClosed) {
				Protocol.SendCommand(stream, ReceiverType.Client_Server, CommandType.Exit);
				isClosed = true;
				stream.Close();
				client.Close();
			}
		}

		public void Dispose() {
			Close();
		}
	}
}
