#include "Utils.h"

int stoi(const string& val)
{
	int res;
	stringstream ss(val);
	ss >> res;
	return res;
}

vector<string> split(const string& src, char delimiter)
{
	vector<string> res;
	string current;

	for (size_t i = 0; i < src.length(); i++) {
		if (src[i] == delimiter) {
			res.push_back(current);
			current = "";
		}
		else
			current += src[i];
	}

	return res;
}