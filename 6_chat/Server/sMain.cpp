#include "func.h"

int main() {
	Init();

	SOCKET serverSocket = OpenTCPIPSocket(), clientSocket;
	sockaddr_in server = FillServerInfo(7654, INADDR_ANY, serverSocket);

	while (1) {
		sockaddr_in client;
		int clientSize = sizeof(client);

		if ((clientSocket = accept(serverSocket, (sockaddr*)&client, &clientSize)) == SOCKET_ERROR) {
			cout << "Accept Failed.";
			return EXIT_FAILURE;
		}

		HOSTENT *clientInfo;
		clientInfo = gethostbyaddr((char *)&client.sin_addr.s_addr, 4, AF_INET);
		cout << "New connect: " << ((clientInfo)? clientInfo->h_name:"") << endl;
		cout << inet_ntoa(client.sin_addr);
		cout << ":" << ntohs(client.sin_port) << endl;


		cout << GetWithLength(clientSocket) << endl;
	}

	closesocket(serverSocket);
	WSACleanup();
	return EXIT_SUCCESS;
}
