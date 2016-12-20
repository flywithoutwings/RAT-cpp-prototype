#pragma once

#include <string>
#include <sstream>
#include <vector>
using namespace std;


int string_to_int(const string& val);
vector<string> split(const string& src, char delimiter);
string parseDir(vector<string>& dir);
void parseDir(vector<string>& dest, const string& dir);