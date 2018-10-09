using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace MyProtocol {
	static public class Protocol {
		static public RecieveResult Recieve(NetworkStream stream, out byte[] data) {
			//Recieve ReceiverType
			data = new byte[1];
			stream.Read(data, 0, 1);
			ReceiverType receiverType = (ReceiverType)data[0];

			//Recieve CommandType
			data = new byte[1];
			stream.Read(data, 0, 1);
			CommandType commandType = (CommandType)data[0];

			if (commandType == CommandType.RawData || commandType == CommandType.String || commandType == CommandType.Connect) {
				//Recieve bytes size
				data = new byte[4];
				stream.Read(data, 0, 4);

				//Recieve bytes
				data = new byte[BitConverter.ToInt32(data, 0)];
				stream.Read(data, 0, data.Length);
			}

			return new RecieveResult(receiverType, commandType);
		}

		static public void SendCommand(NetworkStream stream, ReceiverType receiverType, CommandType type, byte[] data = null) {
			if (type == CommandType.String || type == CommandType.RawData)
				throw new Exception("Wrong command");

			BaseSend(stream, receiverType, type, data);
		}

		static public void SendRawData(NetworkStream stream, ReceiverType receiverType, byte[] data) {
			BaseSend(stream, receiverType, CommandType.RawData, data);
		}

		static public void SendString(NetworkStream stream, ReceiverType receiverType, string message) {
			BaseSend(stream, receiverType, CommandType.String, Encoding.UTF8.GetBytes(message));
		}

		static void BaseSend(NetworkStream stream, ReceiverType receiverType, CommandType commandType, byte[] data) {
			//Send ReceiverType
			byte[] intBytes = BitConverter.GetBytes((byte)receiverType);
			stream.Write(intBytes, 0, 1);

			//Send CommandType
			intBytes = BitConverter.GetBytes((byte)commandType);
			stream.Write(intBytes, 0, 1);

			if (data != null) {
				//Send bytes size
				intBytes = BitConverter.GetBytes(data.Length);
				stream.Write(intBytes, 0, 4);
				//Send bytes
				stream.Write(data, 0, data.Length);
			}
		}

		static public bool IsServerMessage(ReceiverType receiverType) {
			return receiverType == ReceiverType.Server_Everyone || receiverType == ReceiverType.Server_GroupById || receiverType == ReceiverType.Server_Client;
		}

		static public bool IsClientMessage(ReceiverType receiverType) {
			return receiverType == ReceiverType.Client_Everyone || receiverType == ReceiverType.Client_GroupById || receiverType == ReceiverType.Client_Server;
		}
	}
}
