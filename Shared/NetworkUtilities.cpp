#include "NetworkUtilities.h"
#include "Utils.h"
#include <iostream>


void _send(SOCKET conn, const SocketData& src)
{
	uint32_t tag_len = htonl(src.tag.size());
	uint32_t data_len = htonl(src.data.size());

	send(conn, (char*)&tag_len, sizeof(uint32_t), NULL);	// Send tag length
	send(conn, (char*)&data_len, sizeof(uint32_t), NULL);	// Send data length
	send(conn, src.tag.c_str(), src.tag.length(), NULL);	// Send tag 
	send(conn, src.data.c_str(), src.data.length(), NULL);	// Send data
}

void _send(SOCKET conn, const string& tag, const string& data) {
	SocketData sd;
	sd.tag = tag;
	sd.data = data;
	_send(conn, sd);
}


void _recv(SOCKET conn, SocketData& dest)
{
	uint32_t data_len, tag_len;

	recv(conn, (char*)&tag_len, sizeof(uint32_t), NULL);		// Recive tag len
	recv(conn, (char*)&data_len, sizeof(uint32_t), NULL);		// Recive data len
		
	tag_len = ntohl(tag_len);									// Decode tag len
	data_len = ntohl(data_len);									// Decode data len

	cout << data_len << endl;

	vector<char> tag_buffer(tag_len);
	vector<char> data_buffer(data_len);

	recv(conn, &(tag_buffer[0]), tag_len, NULL);				// Recive tag
	recv(conn, &(data_buffer[0]), data_len, NULL);				// Recive data

	dest.tag.assign(&(tag_buffer[0]), tag_buffer.size());		// Assign tag buffer to the destination SocketData
	dest.data.assign(&(data_buffer[0]), data_buffer.size());	// Assign data buffer to the destination SocketData

	cout << "SOCKET: [" << dest.tag << "] -> " << dest.data << endl;
}