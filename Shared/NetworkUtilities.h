#pragma once

#pragma comment (lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <vector>
using namespace std;

typedef struct {
	string tag;
	string data;
} SocketData;


void _send(SOCKET conn, const SocketData& src);
void _send(SOCKET conn, const string& tag, const string& data);

void _recv(SOCKET conn, SocketData& dest);