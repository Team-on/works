using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace MyProtocol {
	static public class Protocol {
		static public byte[] Recieve(NetworkStream stream) {
			byte[] data = new byte[4];
			stream.Read(data, 0, 4);
			data = new byte[BitConverter.ToInt32(data, 0)];
			Console.WriteLine("Rec: " + data.Length);
			stream.Read(data, 0, data.Length);
			return data;
		}

		static public void Send(NetworkStream stream, string message) {
			Send(stream, Encoding.UTF8.GetBytes(message));
		}

		static public void Send(NetworkStream stream, byte[] data) {
			byte[] intBytes = BitConverter.GetBytes(data.Length);
			stream.Write(intBytes, 0, 4);
			Console.WriteLine("Sen: " + data.Length);
			stream.Write(data, 0, data.Length);
		}
	}
}
