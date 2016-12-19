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
		int error = _recv_wait(client->conn, sData);

		if (error != 0) {
			cout << "CLIENT DISCONNECTED" << endl;
			return;
		}

		client->packets.push(sData);

		//cout << "\tRECIVED [" << client->id << "]:" << sData.tag << " -> " << sData.data << endl;
	}
}