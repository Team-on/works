#ifndef _FUNC_H_
#define _FUNC_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
#define MAX_MESSAGE_SIZE 4096

void Init();

SOCKET OpenTCPIPSocket();

sockaddr_in FillServerInfo(unsigned short port, const char *addres, SOCKET toBind = 0);
void ConnectToServer(SOCKET socket, sockaddr_in server);

void SendWithLength(SOCKET sender, const char * message);
string GetWithLength(SOCKET sender);


#endif