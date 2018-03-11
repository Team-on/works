#ifndef _INI_PARSER_H_
#define _INI_PARSER_H_

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define INI_PARSER_MAX_LENGTH 255

class IniParser {
	fstream file;
	char *fileName;

	bool FindSection(const string secName);
	bool IsComment(char ch);

	void ClearStr(char*& str);
	string* ReadSectionValues(string _section, bool ingoreComment);
public:
	IniParser();
	IniParser(const char *fileName);
	IniParser(const char *argv0, const char *fileName);
	IniParser(const string &fileName);
	~IniParser();

	void Open(const char *fileName);
	void Open(const char *argv0, const char *fileName);
	void Open(const string &fileName);
	bool IsOpen();
	void Close();

	char * GetFileName() const;

	void CreateSection(string _section);

	string* ReadSection();
	string* ReadSections(string _section);
	string* ReadSectionValues(string _section);

	string ReadString(const string section, const string key);
	string ReadBool(const string section, const string key);
	int ReadInt(const string section, const string key);

	void WriteBool(const string section, const string key, bool value);
	void WriteInteger(const string section, const string key, int value);
	void WriteString(const string section, const string key, string value);

	void EraseSection(const string section);
	void DeleteKey(const string section, const string key);

};

#endif // !_INI_PARSER_H_



