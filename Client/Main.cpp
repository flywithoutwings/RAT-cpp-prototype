#include "../Shared/NetworkUtilities.h"
#include "../Shared/Utils.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
using namespace std;

#define DEBUG
#define ADDR "127.0.0.1"
#define PORT 443
#define BUF_SIZE 512


int main(int argc, char** argv) {
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData)) {
#ifdef DEBUG
		cout << "Winsock startup failed" << endl;
#endif
		exit(1);
	}

	SOCKADDR_IN addr;
	int addr_len = sizeof(addr);
	inet_pton(AF_INET, ADDR, &addr.sin_addr);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	SOCKET conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(conn, (SOCKADDR*)&addr, addr_len) == INVALID_SOCKET) {
#ifdef DEBUG
		cout << "Can't connect to " << ADDR << ":" << PORT << endl;
#endif
		exit(1);
	}

#ifdef DEBUG
	cout << "Connected!" << endl;
#endif

	SocketData sData;
	
	_recv(conn, sData);
	_send(conn, sData);

#ifdef DEBUG
	cout << "MOTD:" << sData.data << endl;
#endif



#ifdef DEBUG
	system("pause");
#endif

	return 0;
}