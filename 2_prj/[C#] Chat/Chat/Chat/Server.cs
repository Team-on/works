﻿using System;
using System.Collections.Generic;
using System.Threading;
using System.Text;
using System.Net;
using System.Net.Sockets;
using MyProtocol;

namespace Server {
	public class Server {
		public const string defaultIp = "127.0.0.1";
		public const ushort defaultPort = 63255;

		string ip;
		ushort port;

		TcpListener server;
		Thread serverThread;
		List<ServerSideUser> users = new List<ServerSideUser>();

		public Server() {
			ip = defaultIp;
			port = defaultPort;
			users = new List<ServerSideUser>();
		}

		public void SetConnection(string ip = defaultIp, ushort port = defaultPort) {
			this.ip = ip;
			this.port = port;

			server = new TcpListener(IPAddress.Parse(ip), port);
			users.Clear();
		}

		public void StartServer() {
			server.Start();

			serverThread = new Thread(ProcessServer);
			serverThread.Start();
		}

		public void StopServer() {
			server.Stop();
			serverThread.Abort();
			SendEveryoneCommand(CommandType.Abort);
			foreach (var user in users) {
				user.thread.Abort();
				user.stream.Dispose();
				user.client.Dispose();
			}
		}

		void ProcessServer() {
			while (true) {
				try {
					TcpClient client = server.AcceptTcpClient();
					Thread clientThread = new Thread(new ParameterizedThreadStart(ProcessClient));
					clientThread.Start(client);
				}
				catch (Exception ex) {

				}
			}
		}

		void ProcessClient(object o) {
			TcpClient client = o as TcpClient;
			if (client is null)
				return;
			NetworkStream stream = client.GetStream();

			byte[] data;
			RecieveResult res;

			ServerSideUser currUser = new ServerSideUser() {
				user = null,
				client = client,
				stream = stream,
				thread = Thread.CurrentThread
			};
			users.Add(currUser);

			bool isRunning = true;
			do {
				while (!stream.CanRead)
					Thread.Sleep(100);

				res = Recieve(stream, out data);

				switch (res.receiverType) {
					case ReceiverType.Client_Server:
						switch (res.commandType) {
							case CommandType.Connect:
								currUser.user = ClientLib.User.Deserialize(data);
								SendEveryone(null, currUser.user.Name + " has connected!");
								break;
							case CommandType.Exit:
								isRunning = false;
								users.Remove(currUser);
								SendEveryone(null, currUser.user.Name + " has left!");
								break;
						}
						break;

					case ReceiverType.Client_Everyone:
						switch (res.commandType) {
							case CommandType.String:
								SendEveryoneUserData(currUser.user);
								SendEveryone(currUser, Encoding.UTF8.GetString(data, 0, data.Length));
								break;
							case CommandType.RawData:
								break;
						}
						break;

					case ReceiverType.Client_GroupById:
						switch (res.commandType) {
							default:
								break;
						}
						break;
				}

			} while (isRunning);

			users.Remove(currUser);
			stream.Close();
			client.Close();
		}

		public RecieveResult Recieve(NetworkStream stream, out byte[] data) {
			return Protocol.Recieve(stream, out data);
		}

		void Send(NetworkStream stream, ReceiverType receiverType, string message) {
			MyProtocol.Protocol.SendString(stream, receiverType, message);
		}

		void Send(NetworkStream stream, ReceiverType receiverType, byte[] data) {
			MyProtocol.Protocol.SendRawData(stream, receiverType, data);
		}

		void Send(NetworkStream stream, ReceiverType receiverType, CommandType command) {
			MyProtocol.Protocol.SendCommand(stream, receiverType, command);
		}

		void SendEveryone(ServerSideUser sender, string message) {
			foreach (var user in users)
				Send(user.stream, sender == null ? ReceiverType.Server_Everyone : ReceiverType.Client_Everyone, message);
		}

		public void SendEveryoneMessage(string message) {
			foreach (var user in users)
				Send(user.stream, ReceiverType.Server_Everyone, message);
		}

		public void SendEveryoneCommand(CommandType commandType) {
			foreach (var user in users)
				Send(user.stream, ReceiverType.Server_Everyone, commandType);
		}

		public void SendEveryoneUserData(ClientLib.User user) {
			byte[] userData = ClientLib.User.Serialize(user);
			foreach (var u in users)
				Protocol.SendUserData(u.stream, ReceiverType.Server_Everyone, userData);
		}

	}
}
