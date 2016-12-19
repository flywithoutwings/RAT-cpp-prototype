#pragma once

#include "../Shared/Utils.h"
#include "Client.h"
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <map>
using namespace std;

void inputController(map<int, Client*>* clients);
void execLine(const string& line);