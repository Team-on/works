using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace MyProtocol {
	static public class Protocol {
		static public CommandType Recieve(NetworkStream stream, out byte[] data) {
			//Recieve command
			data = new byte[1];
			stream.Read(data, 0, 1);
			CommandType command = (CommandType)data[0];

			if (command == CommandType.RawData || command == CommandType.String || command == CommandType.Connect) {
				//Recieve bytes size
				data = new byte[4];
				stream.Read(data, 0, 4);

				//Recieve bytes
				data = new byte[BitConverter.ToInt32(data, 0)];
				stream.Read(data, 0, data.Length);
			}

			return command;
		}

		static public void SendCommand(NetworkStream stream, CommandType type, byte[] data = null) {
			if (type == CommandType.String || type == CommandType.RawData)
				throw new Exception("Wrong command");

			BaseSend(stream, type, data);
		}

		static public void SendRawData(NetworkStream stream, byte[] data) {
			BaseSend(stream, CommandType.RawData, data);
		}

		static public void SendString(NetworkStream stream, string message) {
			BaseSend(stream, CommandType.String, Encoding.UTF8.GetBytes(message));
		}

		static void BaseSend(NetworkStream stream, CommandType type, byte[] data) {
			//Send command
			byte[] intBytes = BitConverter.GetBytes((byte)type);
			stream.Write(intBytes, 0, 1);

			if (data != null) {
				//Send bytes size
				intBytes = BitConverter.GetBytes(data.Length);
				stream.Write(intBytes, 0, 4);
				//Send bytes
				stream.Write(data, 0, data.Length);
			}
		}
	}
}
