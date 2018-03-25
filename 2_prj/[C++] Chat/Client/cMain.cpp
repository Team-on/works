#include "../Server/func.h"
#include "../Server/func.cpp"

int main(){
	Init();

	SOCKET clientSocket = OpenTCPIPSocket();
	sockaddr_in server = FillServerInfo(7654, "localhost");
	
	ConnectToServer(clientSocket, server);

	while (1) {
		string mess;
		getline(cin, mess);

		SendWithLength(clientSocket, mess.c_str());
	}
	
	closesocket(clientSocket);
	WSACleanup();
	return EXIT_SUCCESS;
}

