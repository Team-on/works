#include <iostream>
#include <string>
using namespace std;
#include "IniParser.h"

int main(int argc, char ** argv) {
	atexit([]() {cout << "\nEND...\n"; system("pause"); });

	IniParser ini;

	ini.Open(argv[0], "system.ini");

	if (!ini.IsOpen()) {
		cout << "Cant create/open";
		exit(EXIT_FAILURE);
	}

	/*
	cout << ini.GetFileName() << endl; cout << endl;

	string *pstr = nullptr;
	pstr = ini.ReadSection();
	for (int pos = 0; pstr[pos][0] != 0; ++pos)
		cout << pstr[pos] << endl;

	delete[] pstr;
	pstr = nullptr;
	cout << endl;

	try{
		pstr = ini.ReadSections("386Enh");
		for (int pos = 0; pstr[pos][0] != 0; ++pos)
			cout << pstr[pos] << endl;
	}
	catch (exception err) {
		cout << err.what();
	}
	delete[] pstr;
	pstr = nullptr;
	cout << endl;

	try {
		pstr = ini.ReadSectionValues("386Enh");
		for (int pos = 0; pstr[pos][0] != 0; ++pos)
			cout << pstr[pos] << endl;
	}
	catch (exception err) {
		cout << err.what();
	}
	delete[] pstr;
	pstr = nullptr;
	cout << endl;
	*/

	ini.CreateSection("loading");

	//ini.WriteString("drivers", "sounds", "123123");
	//ini.WriteBool("drivers", "IsBOOL", 1);
	//ini.WriteInteger("drivers", "INTEGER", -323232);

	//ini.EraseSection("drivers");
	//ini.DeleteKey("drivers", "wave");

	/*
	string rezS;
	try {
		rezS = ini.ReadString("drivers", "timer");
		cout << rezS;
	}
	catch (exception err) {
			cout << err.what();
	}
	cout << endl;

	string & rezB = rezS;
	try {
		rezB = ini.ReadBool("mysection", "bool");
		cout << rezB;
	}
	catch (exception err) {
		cout << err.what();
	}
	cout << endl;

	int rezI;
	try {
		rezI = ini.ReadInt("mysection", "int");
		cout << rezI;
	}
	catch (exception err) {
		cout << err.what();
	}
	cout << endl;
	*/

	return EXIT_SUCCESS;
}
