#include "ClientUtils.h"


string exec(const string& cmd)
{
	string command = cmd;

    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
    if (!pipe)
    	return "ERROR: popen() failed!";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }

	return result;
}

string exec(vector<string>& dir, const string& cmd)
{
	string command;

	command = dir[0] + " && ";

	if (dir.size() > 1)
		command += "cd \"" + parseDir(dir) + "\" && ";

	command += cmd;
	cout << "__EXEC->DIR: " << command << endl;

	/*if (dir.size() == 1)
		command = "cd \\ && " + cmd;
	else if (dir.size() > 1)
		command = "cd " + parseDir(dir) + " && " + cmd;
	else
		command = cmd;*/

    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
    if (!pipe)
    	return "ERROR: popen() failed!";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }

	return result;
}

string getMAC()
{
	string mac;
	regex macAdress("(([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2}))");
	string result = exec("getmac -v");
	sregex_iterator next(result.begin(), result.end(), macAdress);
	sregex_iterator end;

	while (next != end) {
		smatch match = *next;
		mac = match.str();
		next++;
	}

	return mac;
}

string getDir()
{
	TCHAR buffer[MAX_PATH+1] = L"";
    GetModuleFileName(NULL, buffer, MAX_PATH);
	wstring temp(buffer);
	return string(temp.begin(), temp.end());
}

string setDirCmd(vector<string>& dir, const string& path) 
{
	string response;

	if (path[1] == ':') {	// Absolute path 
		DWORD ftyp = GetFileAttributesA(path.c_str());

		if (ftyp == INVALID_FILE_ATTRIBUTES) {
			response = "ERROR CHANGING DIR";
		}
		else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
			parseDir(dir, path);
			response = "DIR SET TO ABSOLUTE PATH: " + path;
		} 
		else {
			response = "ERROR, DIRECTORY NOT FOUND";
		}
	}
	else {	// Relative path
		vector<string> newDir;

		if (path == "..") {
			if (dir.size() >= 2) {
				for (int i = 0; i < dir.size() - 1; i++) {
					newDir.push_back(dir[i]);
				}
				response = "DIR SET TO: " + parseDir(newDir);
			}
		}
		else if (path == "\\") {
			newDir.push_back(dir[0]);
			response = "DIR SET TO: " + parseDir(newDir);
		}
		else {
			newDir = dir;
			newDir.push_back(path);
			string newDirStr = parseDir(newDir);

			DWORD ftyp = GetFileAttributesA(newDirStr.c_str());

			if (ftyp == INVALID_FILE_ATTRIBUTES) {
				response = "ERROR CHANGING DIR";
			}
			else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
				response = "DIR SET TO: " + newDirStr;
			} 
			else {
				response = "ERROR, DIRECTORY NOT FOUND";
			}
		}

		dir = newDir;
		response = "DIR SET TO: " + parseDir(newDir);
	}
				
	return response;
}

string getAllFiles(const string& dir)
{
	HANDLE hFind;
	WIN32_FIND_DATA data;

	string result = "";

	hFind = FindFirstFile((LPCWSTR)dir.c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			printf("%s\n", data.cFileName);
			wstring temp(data.cFileName);
			result += string(temp.begin(), temp.end()) + "\n";
			printf("%s\n", data.cFileName);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}

	return result;
}