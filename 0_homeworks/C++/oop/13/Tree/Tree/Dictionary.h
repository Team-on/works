#ifndef _DICTIONATY_H_
#define _DICTIONATY_H_

#include <iostream>
#include <fstream>

using namespace std;

class DictionaryWord {
	char *lang1, *lang2;
	int callTimes;

public:
	DictionaryWord() : callTimes(0), lang1(nullptr), lang2(nullptr) { }
	DictionaryWord(const DictionaryWord &rhs) {
		if (rhs.lang1 != nullptr) {
			lang1 = new char[strlen(rhs.lang1) + 1];
			strcpy(lang1, rhs.lang1);
		}
		else
			lang1 = nullptr;
		if (rhs.lang2 != nullptr) {
			lang2 = new char[strlen(rhs.lang2) + 1];
			strcpy(lang2, rhs.lang2);
		}
		else
			lang2 = nullptr;
		callTimes = rhs.callTimes;
	}
	DictionaryWord(char *Lang1) : callTimes(0) {
		lang1 = new char[strlen(Lang1) + 1];
		strcpy(lang1, Lang1);
		lang2 = nullptr;
		lang2 = new char[1];
		strcpy(lang2, "");
	}
	DictionaryWord(char *Lang1, char *Lang2) : callTimes(0) {
		lang1 = new char[strlen(Lang1) + 1];
		strcpy(lang1, Lang1);
		lang2 = new char[strlen(Lang2) + 1];
		strcpy(lang2, Lang2);
	}
	~DictionaryWord() {
		if (lang1 != nullptr)
			delete[] lang1;
		if (lang2 != nullptr)
			delete[] lang2;
	}

	int GetCallTimes() const {
		return callTimes;
	}
	void SetCallTimes(int Ct) {
		callTimes = Ct;
	}

	bool operator==(DictionaryWord& rhs) {
		return strcmp(lang1, rhs.lang1) == 0;
	}
	bool operator!=(DictionaryWord& rhs) {
		return !(*this == rhs);
	}
	bool operator>(DictionaryWord& rhs) {
		return strcmp(lang1, rhs.lang1) == -1;
	}
	bool operator>=(DictionaryWord& rhs) {
		return *this > rhs || *this == rhs;
	}
	bool operator<(DictionaryWord& rhs) {
		return !(*this >= rhs);
	}
	bool operator<=(DictionaryWord& rhs) {
		return !(*this > rhs);
	}

	DictionaryWord& operator=(const DictionaryWord& rhs) {
		if (this == &rhs)
			return *this;
		if (lang1 != nullptr)
			delete[] lang1;
		if (lang2 != nullptr)
			delete[] lang2;
		if (rhs.lang1 != nullptr) {
			lang1 = new char[strlen(rhs.lang1) + 1];
			strcpy(lang1, rhs.lang1);
		}
		else
			lang1 = nullptr;
		if (rhs.lang2 != nullptr) {
			lang2 = new char[strlen(rhs.lang2) + 1];
			strcpy(lang2, rhs.lang2);
		}
		else
			lang2 = nullptr;
		callTimes = rhs.callTimes;
	}

	void ParseDictionaryMuller(ifstream &fin) {
		char line[10000], engw[500] = { 0 }, uaw[10000] = { 0 };
		while (!fin.eof()) {

			fin.getline(line, 199);
			if ((line[0] >= 'a' && line[0] <= 'z') ||
				(line[0] >= 'A' && line[0] <= 'Z')) {

				if (engw[0] != 0) {
					cout << engw << "  ";
					if (uaw[0] != 0)
						cout << uaw << endl;
				}

				for (int i = 0; i < 500; ++i)
					engw[i] = 0;
				for (int i = 0; i < 10000; ++i)
					uaw[i] = 0;

				char cnt = 0;
				while ((line[cnt] >= 'a' && line[cnt] <= 'z') ||
					(line[cnt] >= 'A' && line[cnt] <= 'Z') ||
					line[cnt] == ' ' ||
					line[cnt] == ';' ||
					line[cnt] == '-' ||
					line[cnt] == '.'
					) {
					engw[cnt] = line[cnt];
					++cnt;
				}
				int cnt2 = cnt;
				cnt = 0;
				while (((line[cnt + cnt2] >= -64 && line[cnt + cnt2] <= -1) ||
					line[cnt + cnt2] == ' ' ||
					line[cnt + cnt2] == ';' ||
					line[cnt + cnt2] == '-' ||
					line[cnt + cnt2] == '.') &&
					line[cnt + cnt2] != '\0'
					) {
					uaw[cnt] = line[cnt + cnt2];
					++cnt;
				}
			}
			else if (line[0] != ' ') {
				char UAcont[10000] = { 0 };
				int cnt = 0;
				while (((line[cnt] >= -64 && line[cnt] <= -1) ||
					line[cnt] == ' ' ||
					line[cnt] == ';' ||
					line[cnt] == '-' ||
					line[cnt] == '.') &&
					line[cnt] != '\0'
					) {
					UAcont[cnt] = line[cnt];
					++cnt;
				}
				strcat(uaw, UAcont);
			}
		}
	}
	bool ParseDictionaryMy(ifstream &fin) {
		if (fin.eof())
			return 0;

		char line[60];
		char engw[30] = { 0 }, uaw[30] = { 0 };
		fin.getline(engw, 29);
		fin.getline(uaw, 29);
		//fin.ignore();
		//fin >> callTimes;
		//fin.ignore();
		if (lang1 != nullptr)
			delete[] lang1;
		if (lang2 != nullptr)
			delete[] lang2;
		lang1 = new char[strlen(engw) + 1];
		strcpy(lang1, engw);
		lang2 = new char[strlen(uaw) + 1];
		strcpy(lang2, uaw);

		fin.getline(uaw, 29);
		callTimes = atoi(uaw);
		fin.ignore();

		if (strcmp(lang1, "") == 0)
			return 0;

		return 1;
	}

	friend ostream& operator<<(ostream& out, DictionaryWord& dic);
	friend ofstream& operator<<(ofstream& fout, DictionaryWord& dic);
	friend istream& operator>>(istream& in, DictionaryWord& dic);
	friend ifstream& operator>>(ifstream& fin, DictionaryWord& dic);
};
ostream& operator<<(ostream& out, DictionaryWord& dic) {
	out << dic.callTimes << "\t" << dic.lang1 << " - " << dic.lang2;
	return out;
}
ofstream& operator<<(ofstream& fout, DictionaryWord& dic) {
	fout << dic.lang1 << endl << dic.lang2 << endl << dic.callTimes << endl;
	return fout;
}
istream& operator>>(istream& in, DictionaryWord& dic) {
	char w1[40], w2[40];
	in.getline(w1, 39);
	in.getline(w2, 39);
	if (dic.lang1 != nullptr)
		delete[] dic.lang1;
	if (dic.lang2 != nullptr)
		delete[] dic.lang2;
	dic.lang1 = new char[strlen(w1) + 1];
	strcpy(dic.lang1, w1);
	dic.lang2 = new char[strlen(w2) + 1];
	strcpy(dic.lang2, w2);
	return in;
}
ifstream& operator>>(ifstream& fin, DictionaryWord& dic) {
	char w1[40], w2[40];
	fin.getline(w1, 39);
	fin.getline(w2, 39); 
	if (dic.lang1 != nullptr)
		delete[] dic.lang1;
	if (dic.lang2 != nullptr)
		delete[] dic.lang2;
	dic.lang1 = new char[strlen(w1) + 1];
	strcpy(dic.lang1, w1);
	dic.lang2 = new char[strlen(w2) + 1];
	strcpy(dic.lang2, w2);
	fin.ignore();
	fin >> dic.callTimes;
	return fin;
}

#endif