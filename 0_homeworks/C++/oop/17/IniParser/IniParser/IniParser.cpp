#include "IniParser.h"

IniParser::IniParser() : fileName(nullptr){ }

IniParser::IniParser(const char *fileName) : IniParser() {
	Open(fileName);
}

IniParser::IniParser(const char *argv0, const char *fileName) : IniParser() {
	Open(argv0, fileName);
}

IniParser::IniParser(const string &fileName) : IniParser() {
	Open(fileName);
}

IniParser::~IniParser() {
	if (IsOpen())
		Close();
}

void IniParser::Open(const char *fileName) {
	file.open(fileName);
	if (this->fileName != nullptr)
		delete[] this->fileName;
	this->fileName = new char[strlen(fileName) + 1];
	for (short i = 0; i < strlen(fileName) + 1; ++i)
		this->fileName[i] = fileName[i];
}

void IniParser::Open(const char *argv0, const char *fileName) {
	char PATH[_MAX_PATH] = { 0 };
	short pos = 0;
	for (; pos < strlen(argv0); ++pos) 
		PATH[pos] = argv0[pos];	
	
	for (; pos >= 0; --pos)
		if (argv0[pos - 1] == '\\')
			break;
	for (short i = 0; i < strlen(fileName) + 1; ++i) 
		PATH[i + pos] = fileName[i];
	
	Open(PATH);
	if (!IsOpen()) {
		ofstream fout(this->fileName);
		fout.close();
		Open(this->fileName);
	}
}

void IniParser::Open(const string &fileName) {
	file.open(fileName);
	if (this->fileName != nullptr)
		delete[] this->fileName;
	this->fileName = new char[fileName.length() + 1];
	for (short i = 0; i < fileName.length() + 1; ++i)
		this->fileName[i] = fileName[i];
}

bool IniParser::IsOpen() {
	return file.is_open();
}

void IniParser::Close() {
	file.close();
	if (fileName != nullptr)
		delete[] fileName;
	fileName = nullptr;
}

char * IniParser::GetFileName() const {
	if (fileName == nullptr)
		throw exception("File not exist");
	return fileName;
}

void IniParser::CreateSection(string _section) {
	char *p = nullptr;
	bool FindSector = 0;
	const string section = "[" + _section + "]";

	if (!file.good())
		file.clear();
	file.seekg(0);

	while (!file.eof()) {
		if (IsComment(file.peek()))
			file.ignore(INI_PARSER_MAX_LENGTH, '\n');
		if (FindSection(section)) {
			FindSector = 1;
		}
		file.get();
	}

	if (!FindSector) {
		file.close();
		ofstream fout(fileName, ios_base::app);
		fout << '\n';
		fout << '\n' << section;
		fout.close();
		file.open(fileName);
	}

}

string* IniParser::ReadSection() {
	if (!file.good())
		file.clear();
	file.seekg(0);
	short sectorCnt = 0;
	while (!file.eof()) {
		if (IsComment(file.peek()))
			file.ignore(INI_PARSER_MAX_LENGTH, '\n');
			if (file.peek() == '[' ) {
				++sectorCnt;
			}
		file.get();
	}

	string *rez = new string[sectorCnt + 1];
	rez[sectorCnt][0] = 0;
	int pos = 0;

	if (!file.good())
		file.clear();
	file.seekg(0);
	while (!file.eof()) {
		if (IsComment(file.peek()))
			file.ignore(INI_PARSER_MAX_LENGTH, '\n');
		if (file.peek() == '[') {
			char line[INI_PARSER_MAX_LENGTH];
			file.getline(line, INI_PARSER_MAX_LENGTH - 1);
			*(strstr(line, "]") + 1) = 0;
			rez[pos++] = line;
		}
		file.get();
	}

	return rez;
}

string* IniParser::ReadSections(string _section) {
	string* rez = ReadSectionValues(_section);

	for (int pos = 0; rez[pos][0] != 0; ++pos) {
		for (int i = 0; i < rez[pos].length(); ++i)
			if (rez[pos][i] == '=') {
				//for (int j = i; j <= rez[pos].length(); ++j)
					//rez[pos][j] = 0;
				rez[pos].resize(i);
				break;
			}
		while(rez[pos][rez[pos].length() - 1] == ' ' || rez[pos][rez[pos].length() - 1] == '\t')
			rez[pos].resize(rez[pos].length() - 1);
	}

	return rez;
}

string* IniParser::ReadSectionValues(string _section, bool ingoreComment) {
	bool FindSector = 0;
	if (!file.good())
		file.clear();
	file.seekg(0);
	short paramCnt = 0;
	const string section = "[" + _section + "]";

	while (!file.eof()) {
		if (IsComment(file.peek()))
			file.ignore(INI_PARSER_MAX_LENGTH, '\n');

		if (FindSection(section)) {
			FindSector = 1;
			while (file.peek() != '[' && !file.eof()) {
				char value[INI_PARSER_MAX_LENGTH];
				file.getline(value, INI_PARSER_MAX_LENGTH - 1);
				if (strstr(value, "=") != NULL)
					++paramCnt;
			}
		}

		file.get();
	}

	if (!FindSector) {
		char exceptionMess[100];
		strcpy(exceptionMess, "Section [");
		char pos = strlen(exceptionMess);
		for (char i = 0; i <= _section.length(); ++i)
			exceptionMess[i + pos] = _section[i];
		strcat(exceptionMess, "] not exist");

		throw exception(exceptionMess);
	}

	string *rez = new string[paramCnt + 1];
	rez[paramCnt][0] = 0;
	int pos = 0;

	if (!file.good())
		file.clear();
	file.seekg(0);
	while (!file.eof()) {
		if (IsComment(file.peek()))
			file.ignore(INI_PARSER_MAX_LENGTH, '\n');

		if (FindSection(section)) {
			while (file.peek() != '[' && !file.eof()) {
				char *value = new char[INI_PARSER_MAX_LENGTH];
				file.getline(value, INI_PARSER_MAX_LENGTH - 1);
				if (strstr(value, "=") != NULL) {
					if(ingoreComment)
						ClearStr(value);
					rez[pos++] = value;
				}
				delete[] value;
			}
		}

		file.get();
	}

	return rez;
}

string* IniParser::ReadSectionValues(string _section) {
	return ReadSectionValues(_section, 1);
}

string IniParser::ReadString(const string _section, const string _key) {
	char *p = nullptr;
	bool FindSector = 0;	
	const string section = "[" + _section + "]";
	char key[65];
	for (char i = 0; i <= _key.length(); ++i)
		key[i] = _key[i];
	if(!file.good())
		file.clear();
	file.seekg(0);

	while (!file.eof()) {
		 if(IsComment(file.peek()))
			file.ignore(INI_PARSER_MAX_LENGTH, '\n');

		if (FindSection(section)) {
			FindSector = 1;
			while (file.peek() != '[' && !file.eof()) {
				char value[INI_PARSER_MAX_LENGTH];
				file.getline(value, INI_PARSER_MAX_LENGTH - 1);
				if (strstr(value, key) != NULL) {
					p = strstr(value, "=") + 1;
					ClearStr(p);
					return p;
				}
			}
		}

		file.get();
	}

	if (p != nullptr)
		return p;

	char exceptionMess[100];
	if (FindSector) {
		strcpy(exceptionMess, "Key [");
		strcat(exceptionMess, key);
	}
	else {
		strcpy(exceptionMess, "Section [");
		char pos = strlen(exceptionMess);
		for (char i = 0; i <= _section.length(); ++i)
			exceptionMess[i + pos] = _section[i];
	}

		strcat(exceptionMess, "] not exist");

	throw exception(exceptionMess);
}

string IniParser::ReadBool(const string section, const string key) {
	string rez = ReadString(section, key);

	if (!(rez == "true" || rez == "false"))
		throw exception("Value not bool");

	return rez;
}

int IniParser::ReadInt(const string section, const string key) {
	string buff = ReadString(section, key);
	if (!( (buff[0] >= '0' && buff[0] <= '9') ||
		 (buff[0] == '-' && buff[1] >= '0' && buff[1] <= '9')
		))
		throw exception("Value not int");

	char *rez = new char[buff.length() + 1];
	for (short i = 0; i < buff.length(); ++i)
		rez[i] = buff[i];
	int rezI = atoi(rez);
	delete[] rez;
	return rezI;
}

void IniParser::WriteBool(const string section, const string key, bool value) {
	WriteString(section, key, value?"true":"false");
}

void IniParser::WriteInteger(const string section, const string key, int value) {
	char num[10];
	itoa(value, num, 10);
	WriteString(section, key, num);
}

void IniParser::WriteString(const string section, const string key, string value) {
	if (!file.good())
		file.clear();
	file.seekg(0, ios_base::end);
	long size = long(file.tellg()) + key.length() + value.length() + 30;
	char *text = new char[size + 1];
	file.seekg(0);
	for (long i = 0; i <= size; ++i)
		text[i] = '\0';

	for (long i = 0; !file.eof(); ++i) {
		text[i] = file.get();

		if (file.peek() == '[') {
			long fPos = file.tellg();
			if (FindSection("[" + section + "]")) {
				++i;
				file.seekg(fPos);
				text[i++] = file.get();
				while ((text[i++] = file.get()) != '\n');
				bool writed = 0;

				do {
					char str[INI_PARSER_MAX_LENGTH];
					file.getline(str, INI_PARSER_MAX_LENGTH - 1);
					if (strstr(str, key.c_str()) == NULL) {
						for (short j = 0; str[j] != 0; ++j)
							text[i++] = str[j];
						text[i++] = '\n';
					}
					else {
						writed = 1;
						for (short j = 0; key[j] != 0; ++j)
							text[i++] = key[j];
						text[i++] = ' ';  text[i++] = '='; text[i++] = ' ';
						for (short j = 0; value[j] != 0; ++j)
							text[i++] = value[j];
						text[i++] = '\n';
					}

				} while (file.peek() != '[' && !file.eof());
				
				if (!writed) {
					while (text[i--] == '\n');
					for (short j = 0; key[j] != 0; ++j)
						text[i++] = key[j];
					text[i++] = ' ';  text[i++] = '='; text[i++] = ' ';
					for (short j = 0; value[j] != 0; ++j)
						text[i++] = value[j];
					text[i++] = '\n';
					text[i++] = '\n';
				}
				--i;
			}
			else
				file.seekg(fPos);
		}

	}

	file.close();
	ofstream fout(fileName, ios_base::trunc);
	fout << text;
	fout.close();
	file.open(fileName);
}

void IniParser::EraseSection(const string section) {
	if (!file.good())
		file.clear();
	file.seekg(0, ios_base::end);
	long size = file.tellg();
	char *text = new char[size + 1];
	file.seekg(0);
	for (long i = 0; i <= size; ++i)
		text[i] = '\0';

	for (long i = 0; !file.eof(); ++i) {
		char tmp = file.get();

		if (file.peek() == '[') {
			long fPos = file.tellg();
			if (FindSection("[" + section + "]")) {
				while (file.get() != '[');
				text[i++] = '\n';
				tmp = '[';
			}
			else
				file.seekg(fPos);
		}

		text[i] = tmp;
	}

	file.close();
	ofstream fout(fileName, ios_base::trunc);
	fout << text;
	fout.close();
	file.open(fileName);
	
	delete[] text;
}

void IniParser::DeleteKey(const string section, const string key) {
	if (!file.good())
		file.clear();
	file.seekg(0, ios_base::end);
	long size = file.tellg();
	char *text = new char[size + 1];
	file.seekg(0);
	for (long i = 0; i <= size; ++i)
		text[i] = '\0';

	for (long i = 0; !file.eof(); ++i) {
		text[i] = file.get();

		if (file.peek() == '[') {
			long fPos = file.tellg();
			if (FindSection("[" + section + "]")) {
				++i;
				file.seekg(fPos);
				text[i++] = file.get();
				while ((text[i++] = file.get()) != '\n');
				
				do {
					char str[INI_PARSER_MAX_LENGTH];
					file.getline(str, INI_PARSER_MAX_LENGTH - 1);
					if (strstr(str, key.c_str()) == NULL) {
						for (short j = 0; str[j] != 0; ++j)
							text[i++] = str[j];
						text[i++] = '\n';
					}

				} while (file.peek() != '[' && !file.eof());	
				--i;
			}
			else
				file.seekg(fPos);
		}

	}

	file.close();
	ofstream fout(fileName, ios_base::trunc);
	fout << text;
	fout.close();
	file.open(fileName);

	delete[] text;
}

bool IniParser::FindSection(const string secName) {
	if (file.peek() == '[') {
		char str[INI_PARSER_MAX_LENGTH];
		file.getline(str, INI_PARSER_MAX_LENGTH - 1);
		return str == secName;
	}
	return 0;
}

bool IniParser::IsComment(char ch) {
	return ch == ';' || ch == '#';
}

void IniParser::ClearStr(char*& p) {
	while (*p == ' ' || *p == '\t')
		++p;

	for (short i = 0; i < strlen(p); ++i) {
		if (IsComment(p[i])) {
			p[i] = 0;
			break;
		}
	}

	while (p[strlen(p) - 1] == ' ' || p[strlen(p) - 1] == '\t')
		p[strlen(p) - 1] = 0;
}
