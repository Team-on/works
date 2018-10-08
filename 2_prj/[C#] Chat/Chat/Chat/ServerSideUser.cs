using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using ClientLib;

namespace Server {
	public class ServerSideUser {
		public ClientLib.User user;
		public TcpClient client;
		public NetworkStream stream;
		public Thread thread;
	}
}
