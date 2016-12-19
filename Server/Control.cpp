#include "Control.h"

#define EXIT_CMD "exit()"
#define SELECT_USER_CMD "select"
#define LIST_USERS_CMD "list"

void execLine(map<string, Client*>* clients, Client* current, const string& line) 
{
	if (line == EXIT_CMD) {
		if (current != NULL) {
			current = NULL;
		}
		else {
			cout << "ANY CLIENT SELECTED (use " SELECT_USER_CMD " <<id>>\n\n";
		}
	}

	else if (line.substr(0, strlen(LIST_USERS_CMD)) == LIST_USERS_CMD) {
		cout << "---------------------" << endl;
		for (map<string, Client*>::iterator it = (*clients).begin(); it != (*clients).end(); it++) {
			cout << it->first << endl;
		}
		cout << "---------------------" << endl << endl;
	}

	else if (line.substr(0, strlen(SELECT_USER_CMD)) == SELECT_USER_CMD) {
		string id = line.substr(strlen(SELECT_USER_CMD) + 1, line.length());
		if ((*clients).find(id) != (*clients).end()) {
			current = (*clients)[id];
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

void inputController(map<string, Client*>* clients)
{
	Client* current = NULL;

	string line;
	while (true) {
		getline(cin, line);
		execLine(clients, current, line);
	}

	
}