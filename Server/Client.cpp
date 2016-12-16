#include "Client.h"

#define CAPTURE_PACKETS_DELAY 50


void initCapture(Client* client)
{
	client->captureThreadHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)captureThread, (LPVOID)client, NULL, NULL);
}

void stopCapture(Client* client)
{
	CloseHandle(client->captureThreadHandle);
}

void captureThread(Client* client)
{
	while (true) {
		Sleep(CAPTURE_PACKETS_DELAY);

		SocketData sData;
		_recv_wait(client->conn, sData);

		client->packets.push(sData);

		cout << "RECIVED:" << sData.tag << " -> " << sData.data << endl;
	}
}