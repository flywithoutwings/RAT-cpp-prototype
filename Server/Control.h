#pragma once

#include "Client.h"
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <map>
using namespace std;

void inputController(map<string, Client*>* clients);
void execLine(const string& line);