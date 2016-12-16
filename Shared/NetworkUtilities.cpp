#include "NetworkUtilities.h"
#include "Utils.h"
#include <iostream>	// REMOVE


void _send(SOCKET conn, const SocketData& src)
{
	uint32_t data_len_encoded = htonl(src.data.size());
	uint32_t tag_encoded = htonl((uint32_t)src.tag);

	send(conn, (char*)&tag_encoded, sizeof(uint32_t), NULL);		// Send tag encoded
	send(conn, (char*)&data_len_encoded, sizeof(uint32_t), NULL);	// Send data length encoded
	send(conn, src.data.c_str(), src.data.length(), NULL);			// Send data
}

void _send(SOCKET conn, const SocketTag tag, const string& data) 
{
	SocketData sd;
	sd.tag = tag;
	sd.data = data;
	_send(conn, sd);
}


void _recv(SOCKET conn, SocketData& dest)
{
	uint32_t data_len, tag;

	recv(conn, (char*)&tag, sizeof(uint32_t), NULL);			// Recive tag
	recv(conn, (char*)&data_len, sizeof(uint32_t), NULL);		// Recive data len
		
	tag = (SocketTag)ntohl(tag);								// Decode tag
	data_len = ntohl(data_len);									// Decode data len

	vector<char> data_buffer(data_len);

	recv(conn, &(data_buffer[0]), data_len, NULL);				// Recive data

	dest.data.assign(&(data_buffer[0]), data_buffer.size());	// Assign data buffer to the destination SocketData
	dest.tag = (SocketTag)tag;									// Assign tag to the destination SocketData

	cout << "SOCKET: [" << dest.tag << "] -> " << dest.data << endl;
}

void _recv_wait(SOCKET conn, SocketData& dest)	// Don't close on timeout
{
	uint32_t data_len, tag;
	int rv = 0;

	while (rv == 0) {
		rv = recv(conn, (char*)&tag, sizeof(uint32_t), NULL);			// Recive tag
	}
	rv = 0;

	while (rv == 0) {
		rv = recv(conn, (char*)&data_len, sizeof(uint32_t), NULL);		// Recive data len
	}
	rv = 0;
		
	tag = (SocketTag)ntohl(tag);								// Decode tag
	data_len = ntohl(data_len);									// Decode data len

	vector<char> data_buffer(data_len);

	while (rv == 0) {
		rv = recv(conn, &(data_buffer[0]), data_len, NULL);				// Recive data
	}
	rv = 0;

	dest.data.assign(&(data_buffer[0]), data_buffer.size());	// Assign data buffer to the destination SocketData
	dest.tag = (SocketTag)tag;									// Assign tag to the destination SocketData

	cout << "SOCKET: [" << dest.tag << "] -> " << dest.data << endl;
}