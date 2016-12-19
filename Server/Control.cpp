#include "Control.h"

#define EXIT_CMD "exit()"
#define SELECT_USER_CMD "select"
#define LIST_USERS_CMD "list"
#define GET_CURRENT_USER_CMD "current"
#define GET_INFO_USER_CMD "info"	// TODO: implement

void execLine(map<int, Client*>* clients, Client* current, const string& line) 
{
	if (line == EXIT_CMD) {
		if (current != NULL) {
			current = NULL;
		}
		else {
			cout << "ANY CLIENT SELECTED, use (" SELECT_USER_CMD " <<id>>)\n\n";
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
		cout << "----------------------" << endl << endl;
	}

	else if (line.substr(0, strlen(GET_CURRENT_USER_CMD)) == GET_CURRENT_USER_CMD) {
		if (current != NULL) {
			cout << "CURRENT USER [" << current->id << "]" << endl;
		}
		else {
			cout << "ANY CLIENT SELECTED, use (" SELECT_USER_CMD " <<id>>)\n\n";
		}
	}

	else if (line.substr(0, strlen(SELECT_USER_CMD)) == SELECT_USER_CMD) {
		int id = string_to_int(line.substr(strlen(SELECT_USER_CMD) + 1, line.length()));
		if ((*clients).find(id) != (*clients).end()) {
			current = (*clients)[id];
			cout << "USER [" << current->id << "] SELECTED" << endl;
		}
		else {
			cout << "USER '" << line << "' NOT FOUND\n\n";
		}
	}

	else {
		if (current == NULL) {
			cout << "INVALID COMMAND '" << line << "'\n\n";
		}
		else {
			SocketData packet;
			_send(current->conn, SocketTag::EXEC, line);
		}
	}
}

void inputController(map<int, Client*>* clients)
{
	Client* current = NULL;

	string line;
	while (true) {
		getline(cin, line);
		execLine(clients, current, line);
	}

	
}