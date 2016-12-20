#include "Utils.h"

int string_to_int(const string& val)
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

string parseDir(vector<string>& dir)
{
	string result = "";

	for (int i = 0; i < dir.size(); i++) {
		result += dir[i];
		if (i < dir.size() - 1)
			result += "\\";
	}

	return result;
}

void parseDir(vector<string>& dest, const string& dir)
{
	string current;

	for (int i = 0; i < dir.length(); i++) {
		if (dir[i] == '\\') {
			dest.push_back(current);
			current = "";
		}
		else {
			current += dir[i];
		}
	}
}