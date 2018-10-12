using System;
using System.Collections.Generic;
using System.Threading;
using System.Text;
using System.Net;
using System.Net.Sockets;

using GameLib;

namespace TicTacToe {
	public class Server {
		public const string defaultIp = "127.0.0.1";
		public const ushort defaultPort = 63100;

		string ip;
		ushort port;

		TcpListener server;
		Thread serverThread;

		Game game;
		List<ServerSideUser> users;

		public Server() {
			ip = defaultIp;
			port = defaultPort;
			game = new Game();
			users = new List<ServerSideUser>(2);
		}

		public void SetConnection(string ip = defaultIp, ushort port = defaultPort) {
			this.ip = ip;
			this.port = port;

			server = new TcpListener(IPAddress.Parse(ip), port);
		}

		public void StartServer() {
			game.StartNewGame();
			users.Clear();
			server.Start();

			serverThread = new Thread(ProcessServer);
			serverThread.Start();
		}

		public void StopServer() {
			server.Stop();
			serverThread.Abort();
		}

		void ProcessServer() {
			while(true) {
				// try {
				TcpClient client = server.AcceptTcpClient();
				Thread clientThread = new Thread(new ParameterizedThreadStart(ProcessClient));
				clientThread.Start(client);
				//}
				//catch (Exception ex) {

				//}
			}
		}

		void ProcessClient(object o) {
			Console.WriteLine("Accept client");
			PlayerType currPlayer = game.GetNextPlayer();
			if(currPlayer == PlayerType.PlayerNone)
				return;

			TcpClient client = o as TcpClient;
			if(client is null)
				return;
			NetworkStream stream = client.GetStream();

			users.Add(new ServerSideUser() { client = client, stream = stream, thread = Thread.CurrentThread });

			Console.WriteLine("Try to send player type");
			byte[] data = new byte[3];
			data[0] = (byte)currPlayer;
			stream.WriteByte(data[0]);
			Console.WriteLine("Send player type");

			bool isRunning = true;
			GameState gameState;
			byte i;

			Console.WriteLine("Wait until 2 players");
			while(users.Count != 2)
				Thread.Sleep(100);
			Console.WriteLine("2 players connected");

			do {
				data[0] = (byte)stream.ReadByte();
				Console.WriteLine("Receive player input");

				gameState = game.MakeTurn(data[0], currPlayer);

				Console.WriteLine("Try to send turn rez");
				stream.WriteByte((byte)(gameState == GameState.CantMakeTurn ? 0 : 1));
				Console.WriteLine("Send turn rez");
				if(gameState == GameState.CantMakeTurn)
					continue;

				if(gameState == GameState.Draw || gameState == GameState.Win0 || gameState == GameState.WinX)
					isRunning = false;

				data[1] = (byte)currPlayer;
				data[2] = (byte)gameState;
				Console.WriteLine("Try to send player input back");
				for(i = 0; i < users.Count; ++i) {
					Console.WriteLine($"\tSend: {data[0]} {data[1]} {data[2]}");
					users[i].stream.Write(data, 0, 3);
				}
				Console.WriteLine("Send player input back");

			} while(isRunning);

			stream.Close();
			client.Close();
		}
	}
}
