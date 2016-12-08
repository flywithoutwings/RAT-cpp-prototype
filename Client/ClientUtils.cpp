#include "ClientUtils.h"


string exec(const char* cmd) 
{
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
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