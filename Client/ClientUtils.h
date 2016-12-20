#pragma once

#include "../Shared/Utils.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <regex>
using namespace std;

string getMAC();
string getDir();
string exec(vector<string>& dir, const string& cmd);
string exec(const string& cmd);
string setDirCmd(vector<string>& dir, const string& path);
string getAllFiles(const string& dir);