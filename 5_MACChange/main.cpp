#include "preCompiled.h"

//#define debug
#define SLEEP_TIME_MINUTES  3

void DeleteFiles();

void Init() {
	atexit([]() {
		system("pause");
		DeleteFiles();
	});
	DeleteFiles();
	SetConsoleTitleA("Danulo ti autist.exe");
}

void CreateFiles() {
	system("arp -a >> mac.txt");
	system("ipconfig /all >> pc.txt");
}

void DeleteFiles() {
	remove("tmp.txt");
	remove("mac.txt");
	remove("pc.txt");
}

void FileToStr(string fName, string &str) {
	ifstream file(fName);
	str = "";
	while (!file.eof())
		str += file.get();
	file.close();
}

bool CheckConnection() {
	return system("ping i.ua -n 2 >> tmp.txt") == 0;
}

void ParseUsedMac(vector <string> &macUsed, string &toParse) {
	time_t first;
	time_t last;
	string sub;

	do {
		first = toParse.find("Physical Address");
		if (first == UINT32_MAX || first == -1)
			break;

		last = toParse.find('\n', first);
		sub = toParse.substr(first, last - first);

		for (size_t i = 0, j = sub.find(':') + 2; j < sub.length(); ++i, ++j)
			sub[i] = sub[j];
		sub.resize(sub.find(' '));
		macUsed.push_back(sub);

		for (size_t i = first; i < last; ++i)
			toParse[i] = ' ';
	} while (1);
}

time_t FindByMask(string str, string mask) {
	time_t maskPos = 0, start = 0;
	for (time_t i = 0; i != str.length(); ++i) {
		if (str[i] == mask[maskPos] || mask[maskPos] == '?')
			++maskPos;
		else {
			start = i;
			maskPos = 0;
		}
		if (maskPos == mask.length())
			return start;
	}
	return -1;
}

void ParseMacToUse(vector <string> &macToUse, string &toParse) {
	time_t prev = 0, next, tmp;
	string curr;

	do {
		next = toParse.find_first_of('\n', prev);
		if (next == UINT32_MAX || next == -1)
			break;
		curr = "";
		for (time_t j = prev; j != next; ++j)
			curr += toParse[j];
		prev = next + 1;

		tmp = curr.find("static");
		if (tmp == UINT32_MAX || tmp == -1) {
			tmp = curr.find("dynamic");
			if (tmp == UINT32_MAX || tmp == -1)
				continue;
		}

		for (size_t i = 0, j = FindByMask(curr, "??-??-??-??-??-??") + 1; j < curr.length(); ++i, ++j)
			curr[i] = curr[j];
		curr.resize(strlen("??-??-??-??-??-??"));

		macToUse.push_back(curr);
	} while (1);
}

void ClearBlackMac(vector <string> &mac) {
	string black[] = { "00-00-00-00-00-00-00-E0", "ff-ff-ff-ff-ff-ff-ff-ff", "ff-ff-ff-ff-ff-ff", "00-00-00-00-00-00" };
	vector<string>::iterator rez;
	time_t length;

	for (auto &i : black) {
		length = 0;
		rez = remove(mac.begin(), mac.end(), i);
		for (auto i = mac.begin(); i != rez; ++i, ++length);
		mac.resize(length);
	}
}

void ChangeMac(string newMac) {
	LSTATUS rez;
	HKEY toRead;
	char *info = new char[newMac.length() + 1];
	strcpy(info, newMac.c_str());

	rez = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
		"SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E972-E325-11CE-BFC1-08002BE10318}\\0000", NULL, 
		KEY_WRITE 
		//KEY_READ
		,&toRead);
#ifdef debug
	cout << rez << ' ' << ERROR_SUCCESS << endl;
#endif // DEBUG

	
	rez = RegSetValueExA(toRead, "NetworkAddress" /*"ttt"*/, 0, REG_SZ, (BYTE*)info, strlen(info) + 1 /*sizeof(info)*/);
#ifdef debug
	cout << rez << ' ' << ERROR_SUCCESS << endl;
#endif // DEBUG

	cout << "NetworkAddress = " << info << "\n\n";
}

void main() {
	Init();
#ifndef debug
	CreateFiles();
#endif

	vector <string> macUsed;
	vector <string> macToUse;
	string toParse;

	FileToStr("pc.txt", toParse);
	ParseUsedMac(macUsed, toParse);
	ClearBlackMac(macUsed);

	FileToStr("mac.txt", toParse);
	ParseMacToUse(macToUse, toParse);
	ClearBlackMac(macToUse);

	cout << "Used MAC:" << endl;
	for (auto &i : macUsed)
		cout << i << endl;

	cout << "MAC to use:" << endl;
	for (auto &i : macToUse)
		cout << i << endl;

	time_t currMac = 0;

	//ChangeMac(macToUse[currMac]);
	cout << endl;
	while (1) {
		if (!CheckConnection()) {
			cout << "No connection. Try to change mac" << endl;

			if (currMac == macToUse.size()) {
				cout << "Parse all macs. Load new portion" << endl;
				currMac = 0;
				ParseMacToUse(macToUse, toParse);
				ClearBlackMac(macToUse);
				cout << "MAC to use:" << endl;
				for (auto &i : macToUse)
					cout << i << endl;
				cout << endl;
			}

			cout << "Try: " << macToUse[currMac] << endl;
			ChangeMac(macToUse[currMac]);
			++currMac;
		}
		else {
			cout << "Found connection. Set up pause at " << SLEEP_TIME_MINUTES << " minutes" << endl;
			Sleep(SLEEP_TIME_MINUTES * 60000);
		}
	}

#ifndef debug
	//DeleteFiles();
#endif
}



