using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using MyProtocol;

namespace ClientLib {
	public class Client : IDisposable {
		public const string defaultIp = "127.0.0.1";
		public const ushort defaultPort = 63255;

		const ushort MAX_MESSAGE_LENGTH = 10000;

		User user;
		string ip;
		ushort port;

		TcpClient client;
		NetworkStream stream;

		public Client() {
			user = new User();
			ip = defaultIp;
			port = defaultPort;
		}

		public void SetConnection(string ip = defaultIp, ushort port = defaultPort) {
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
					case CommandType.Abort:
						Abort();
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
		public void Abort() {
			if (!isClosed) {
				isClosed = true;
				stream.Close();
				client.Close();
			}
		}

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
