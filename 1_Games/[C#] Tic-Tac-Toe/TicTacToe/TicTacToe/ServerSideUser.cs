using System.Threading;
using System.Net.Sockets;

namespace TicTacToe {
    public class ServerSideUser {
        public TcpClient client;
        public NetworkStream stream;
        public Thread thread;
    }
}
