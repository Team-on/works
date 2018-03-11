#include "func.h"

void Init() {
	atexit([]() {
		cout << "\nPress any key to exit\n";
		_getch();
	});

	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) {
		cout << "Could Not Start Up Winsock.";
		exit(EXIT_FAILURE);
	}
}

sockaddr_in FillServerInfo(unsigned short port, const char *addres, SOCKET toBind) {
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (addres != INADDR_ANY) {
		unsigned long ipServer = inet_addr(addres);
		if (ipServer == SOCKET_ERROR) {
			hostent *host_entry = gethostbyname(addres);
			if (host_entry == NULL) {
				cout << "Could not find host.";
				exit(EXIT_FAILURE);
			}
			server.sin_addr.s_addr = *(unsigned long*)host_entry->h_addr;
		}
		else {
			server.sin_addr.s_addr = ipServer;
		}
	}
	else {
		server.sin_addr.s_addr = INADDR_ANY;
	}

	if (toBind) {
		if (bind(toBind, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			cout << "Bind Failed.";
			exit(EXIT_FAILURE);
		}
		if (listen(toBind, 32) == SOCKET_ERROR) {
			cout << "Listen Failed.";
			exit(EXIT_FAILURE);
		}
	}

	return server;
}

void ConnectToServer(SOCKET socket, sockaddr_in server) {
	if (connect(socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		cout << "Error connecting to server.";
		exit(EXIT_FAILURE);
	}
}

SOCKET OpenTCPIPSocket() {
	SOCKET sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
		cout << "Error Opening Socket.";
		exit(EXIT_FAILURE);
	}
	return sock;
}

void SendWithLength(SOCKET sender, const char * message) {
	unsigned long messageSize = htonl(strlen(message));

	if (send(sender, (char*)&messageSize, sizeof(messageSize), 0) == SOCKET_ERROR)
		cout << "Send size Failed!\n";

	messageSize = ntohl(messageSize);

	if (send(sender, message, messageSize, 0) == SOCKET_ERROR)
		cout << "Send message Failed!\n";
}

string GetWithLength(SOCKET sender) {
	char buffer[MAX_MESSAGE_SIZE];
	unsigned long messageSize;

	if (recv(sender, (char*)&messageSize, sizeof(messageSize), 0) == SOCKET_ERROR)
		cout << "Recv size Failed!\n";

	messageSize = ntohl(messageSize);

	if (recv(sender, buffer, messageSize, 0) == SOCKET_ERROR)
		cout << "Recv message Failed!\n";

	buffer[messageSize] = '\0';
	return buffer;
}
