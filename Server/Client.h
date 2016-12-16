#pragma once

#include "../Shared/NetworkUtilities.h"
#include <queue>
#include <iostream>
#include <thread>
using namespace std;


typedef struct client_t {
	SOCKET conn;
	HANDLE captureThreadHandle;
	queue<SocketData> packets;
	string id;
} Client;

void initCapture(Client* client);
void stopCapture(Client* client);
void captureThread(Client* client);