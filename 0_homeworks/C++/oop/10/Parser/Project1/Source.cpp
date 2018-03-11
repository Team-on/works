#include <iostream>
#include <fstream>
#include <iomanip>
#include  "Menu.h"
#include <vector>
using namespace std;

struct LINK_CONT {
	char *link;
	int cnt;

	LINK_CONT() {
		link = nullptr;
		cnt = 1;
	}
	LINK_CONT(const char *l) {
		link = new char[strlen(l) + 1];
		strcpy(link, l);
		cnt = 1;
	}
	LINK_CONT(LINK_CONT &rhs) {
		cnt = rhs.cnt;
		if (rhs.link != nullptr) {
			link = new char[strlen(rhs.link) + 1];
			strcpy(link, rhs.link);
		}
		else
			link = nullptr;
	}
	
	~LINK_CONT() {
		if (link != nullptr)
			delete[] link;
	}

	LINK_CONT& operator=(const LINK_CONT& rhs) {
		if (this == &rhs)
			return *this;
		if (link != nullptr)
			delete[] link;
		cnt = rhs.cnt;
		if (rhs.link != nullptr) {
			link = new char[strlen(rhs.link) + 1];
			strcpy(link, rhs.link);
		}
		else
			link = nullptr;

		return *this;
	}

	bool operator==(const LINK_CONT& rhs) {
		if (link == nullptr || rhs.link == nullptr)
			return 0;

		return strcmp(link, rhs.link) == 0;
	}

	friend ostream& operator<<(ostream& out, LINK_CONT& dic);
	friend ofstream& operator<<(ofstream& fout, LINK_CONT& dic);
};
ostream& operator<<(ostream& out, LINK_CONT& dic) {
	out << dic.cnt << " - " << dic.link;
	return out;
}
ofstream& operator<<(ofstream& fout, LINK_CONT& dic) {
	fout << dic.cnt << " - " << dic.link;
	return fout;
}

class ValuteParser {
public:
	enum VALUTE_TYPES { USD, EUR, RUB, QBP, CHF, PLN, JPY, CAD, AUD, DKK, NOK, SZK, ILS, HUF, VALUTE_CNT };
private:
	double KURS[VALUTE_CNT][4][2];
	char VALUTE_IDENTIFY[VALUTE_CNT][74]{
		"<a href=\"https://kurs.com.ua/valyuta/usd/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/eur/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/rub/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/gbp/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/chf/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/pln/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/jpy/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/cad/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/aud/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/dkk/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/nok/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/czk/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/ils/\" class=\"ipsKurs_currency\" title",
		"<a href=\"https://kurs.com.ua/valyuta/huf/\" class=\"ipsKurs_currency\" title"
	};
	char VALUTE_NAMES[VALUTE_CNT][4]{
		"usd",
		"eur",
		"rub",
		"gbp",
		"chf",
		"pln",
		"jpy",
		"cad",
		"aud",
		"dkk",
		"nok",
		"czk",
		"ils",
		"huf"
	};

	LINK_CONT links[200];
	int lSize;

	char argv[_MAX_PATH];
public:
	ValuteParser(char *argv[]) {
		strcpy(this->argv, argv[0]);
		ifstream fin;
		{
			char *PATH = new char[_MAX_PATH];
			strcpy(PATH, argv[0]);
			for (char *i = &PATH[strlen(PATH) - 1]; i != &PATH[0]; --i)
				if (*i == '\\') {
					strcpy(i + 1, "kurs_val\\kurs.html");
					break;
				}
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << PATH << endl;
				delete[] PATH;
				system("pause");
				exit(-1);
			}
			delete[] PATH;
		}

		while (fin.peek() != EOF) {
			const unsigned short bufferSize = 10000;
			char currStr[bufferSize];
			fin.getline(currStr, bufferSize);

			char *seq = nullptr;
			for (int i = 0; i < VALUTE_CNT; ++i) {
				seq = strstr(currStr, VALUTE_IDENTIFY[i]);
				if (seq != nullptr)
					break;
			}
			//char *seq = strstr(currStr, VALUTE_IDENTIFY[USD]);
			if (seq != nullptr) {
				VALUTE_TYPES currValute = VALUTE_CNT;
				int currColumn = 0;
				bool isValue = 0;

				char *seq2 = seq;
				for (int i = 0; i < VALUTE_CNT; ++i) {
					seq2 = strstr(seq, VALUTE_NAMES[i]);
					if (seq2 != nullptr) {
						currValute = VALUTE_TYPES(i);
						break;
					}
				}


				if (currValute == VALUTE_CNT)
					continue;

				while (currColumn != 4) {
					char currStr[bufferSize];
					fin.getline(currStr, bufferSize);
					char *p = strstr(currStr, "data-rate=\"");
					if (p != nullptr) {
						p += 11;
						double currKurs = atof(p);
						KURS[currValute][currColumn][isValue] = currKurs;
						if (isValue) {
							isValue = 0;
							currColumn++;
						}
						else
							isValue = 1;
					}
				}

			}
		}
		fin.close();
	}

	void ParseLinks() {
		lSize = 0;
		ifstream fin;
		{
			char *PATH = new char[_MAX_PATH];
			strcpy(PATH, argv);
			for (char *i = &PATH[strlen(PATH) - 1]; i != &PATH[0]; --i)
				if (*i == '\\') {
					strcpy(i + 1, "kurs_val\\kurs.html");
					break;
				}
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << PATH << endl;
				delete[] PATH;
				system("pause");
				exit(-1);
			}
			delete[] PATH;
		}

		while (fin.peek() != EOF) {
			const unsigned short bufferSize = 10000;
			char currStr[bufferSize];
			fin.getline(currStr, bufferSize);
			char *seq = nullptr;

			seq = strstr(currStr, "https://");
			if (seq != nullptr) {
				char *k;
				k = strstr(seq, "\"");
				if(k != nullptr)
					*k = 0;
				k = strstr(seq, ";");
				if (k != nullptr)
					*k = 0;
				k = strstr(seq, "url");
				if (k != nullptr)
					*k = 0;
				k = strstr(seq, "u=http");
				if (k != nullptr)
					*k = 0;

				k = strstr(seq, ".com.ua");
				if (k != nullptr)
					*(k + 7) = 0;
				else if ((k = strstr(seq, ".com.ru")) != nullptr)
					*(k + 7) = 0;
				else if ((k = strstr(seq, ".ua")) != nullptr)
					*(k + 3) = 0;
				else if ((k = strstr(seq, ".ru")) != nullptr)
					*(k + 3) = 0;
				else if ((k = strstr(seq, ".com")) != nullptr)
					*(k + 4) = 0;
				else if ((k = strstr(seq, ".org")) != nullptr)
					*(k + 4) = 0;
				else if ((k = strstr(seq, ".")) != nullptr)
					*(k + 1) = 0;

					char *kkk;
					for (kkk = seq; *kkk != '\"'; ++kkk);
					*kkk = 0;
					LINK_CONT lin(seq);
					int i = 0;
					for (; i < lSize; ++i) {
						if (links[i] == lin) {
							++links[i].cnt;
							break;
						}
					}
					if (i == lSize) {
						links[lSize++] = lin;
					}
			}

			seq = strstr(currStr, "http://");
			if (seq != nullptr) {
				char *k;
				k = strstr(seq, "\"");
				if (k != nullptr)
					*k = 0;
				k = strstr(seq, ";");
				if (k != nullptr)
					*k = 0;
				k = strstr(seq, "url");
				if (k != nullptr)
					*k = 0;
				k = strstr(seq, "u=http");
				if (k != nullptr)
					*k = 0;

				k = strstr(seq, ".com.ua");
				if (k != nullptr)
					*(k + 7) = 0;
				else if ((k = strstr(seq, ".com.ru")) != nullptr)
					*(k + 7) = 0;
				else if ((k = strstr(seq, ".ua")) != nullptr)
					*(k + 3) = 0;
				else if ((k = strstr(seq, ".ru")) != nullptr)
					*(k + 3) = 0;
				else if ((k = strstr(seq, ".com")) != nullptr)
					*(k + 4) = 0;
				else if ((k = strstr(seq, ".org")) != nullptr)
					*(k + 4) = 0;
				else if ((k = strstr(seq, ".")) != nullptr)
					*(k + 1) = 0;

				char *kkk;
				for (kkk = seq; *kkk != '\"'; ++kkk);
				*kkk = 0;
				LINK_CONT lin(seq);
				int i = 0;
				for (; i < lSize; ++i) {
					if (links[i] == lin) {
						++links[i].cnt;
						break;
					}
				}
				
				if (i == lSize) {
					links[lSize++] = lin;
				}
			}
		}
		fin.close();
	}

	void SortLinks() {
		for (int i = 0; i < lSize; ++i) {
			int min = i;
			for (int j = i; j < lSize; ++j)
				if (links[min].cnt < links[j].cnt)
					min = j;
			if (i != min) {
				swap(links[min].cnt, links[i].cnt);
				swap(links[min].link, links[i].link);
			}
		}
	}
	void SaveLinks(const char DBName[]) const {
		cout << "Save links to link.txt? y/n ";
		char in;
		cin >> in;
		in = tolower(in);
		if (in == 'y') {
			ofstream fout;
			{
				char *PATH = new char[_MAX_PATH];
				strcpy(PATH, argv);
				for (char *i = &PATH[strlen(PATH) - 1]; i != &PATH[0]; --i)
					if (*i == '\\') {
						strcpy(i + 1, DBName);
						break;
					}
				fout.open(PATH);
				if (!fout.is_open()) {
					cout << "Cant save to " << PATH << endl;
					delete[] PATH;
					system("pause");
				}
				delete[] PATH;
			}
			for (int i = 0; i < lSize; ++i)
				fout << links[i].cnt << " - " << links[i].link << endl;
			fout.close();
		}
	}
	void PrintLinks() {
		for (int i = 0; i < lSize; ++i)
			cout << links[i] << endl;
	}

	void Print() const {
		cout << setprecision(6);
		for (int val = 0; val < VALUTE_CNT; ++val) {
			cout << VALUTE_NAMES[val] << ":  ";
			for (int col = 0; col < 4; ++col) 
				cout << setw(11) << KURS[val][col][0];	
			cout << endl << "      ";
			for (int col = 0; col < 4; ++col)
				cout << setw(11) << KURS[val][col][1];
			cout << endl << endl;
		}	
	}
	void PrintValuteId() const {
		for (int val = 0; val < VALUTE_CNT; ++val) {
			cout << val << ' ' << VALUTE_NAMES[val] << '\n';
		}
	}

	const char* GetValuteName(int id) const {
		return VALUTE_NAMES[id];
	}

	void DBSave(const char DBName[]) const {
		ofstream fout;
		{
			char *PATH = new char[_MAX_PATH];
			strcpy(PATH, argv);
			for (char *i = &PATH[strlen(PATH) - 1]; i != &PATH[0]; --i)
				if (*i == '\\') {
					strcpy(i + 1, DBName);
					break;
				}
			fout.open(PATH);
			if (!fout.is_open()) {
				cout << "Cant save to " << PATH << endl;
				delete[] PATH;
				system("pause");
			}
			delete[] PATH;
		}
#define cout fout
		for (int val = 0; val < VALUTE_CNT; ++val) {
			cout << VALUTE_NAMES[val] << ":  ";
			for (int col = 0; col < 4; ++col)
				cout << setw(11) << KURS[val][col][0];
			cout << endl << "      ";
			for (int col = 0; col < 4; ++col)
				cout << setw(11) << KURS[val][col][1];
			cout << endl << endl;
		}
#undef cout
		fout.close();
	}

	void DBRead(const char DBName[]) {
		ifstream fin;
		{
			char *PATH = new char[_MAX_PATH];
			strcpy(PATH, argv);
			for (char *i = &PATH[strlen(PATH) - 1]; i != &PATH[0]; --i)
				if (*i == '\\') {
					strcpy(i + 1, DBName);
					break;
				}
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant read from " << PATH << endl;
				delete[] PATH;
				system("pause");
			}
			delete[] PATH;
		}
		for (int val = 0; val < VALUTE_CNT; ++val) {
			for (int col = 0; col < 4; ++col)
				fin >> KURS[val][col][0];
			for (int col = 0; col < 4; ++col)
				fin >>  KURS[val][col][1];
		}

		fin.close();
	}

	//Convert GRN to another valute
	template <typename T>
	double ConvertFromGRN(VALUTE_TYPES typeTo, T GRN) const {
		return double(GRN) / KURS[typeTo][0][0];
	}
	template <typename T>
	double ConvertToGRN(VALUTE_TYPES typeFrom, T money) const {
		return double(money) * KURS[typeFrom][0][0];
	}
	template <typename T>
	double ConvertFromTo(VALUTE_TYPES typeFrom, VALUTE_TYPES typeTo, T money) const {
		return ConvertFromGRN(typeTo, ConvertToGRN(typeFrom, money));
	}
};


int main(int argc, char *argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ValuteParser parser(argv);

	char menu;
	do {
		menu = MenuMode(
			"Print",
			"Convert From GRN",
			"Convert To GRN",
			"Convert From 1 To 2",
			"Links",
			"Exit",
			""
		);

		switch (menu) {
		case 0: 
		{
			parser.Print();
			system("pause");
		}
		break;
		case 1:
		{
			parser.PrintValuteId();
			int id, money;
			cout << "ID:\n>";
			cin >> id;
			cout << "Money in grn:\n>";
			cin >> money;
			cout << "Money in " << parser.GetValuteName(id) << ":\n>" << parser.ConvertFromGRN(ValuteParser::VALUTE_TYPES(id), money) << endl;
			system("pause");
		}
		break;
		case 2:
		{
			parser.PrintValuteId();
			int id, money;
			cout << "ID:\n>";
			cin >> id;
			cout << "Money in " << parser.GetValuteName(id) << ":\n>";
			cin >> money;
			cout << "Money in grn:\n>" << parser.ConvertToGRN(ValuteParser::VALUTE_TYPES(id), money) << endl;
			system("pause");
		}
		break;
		case 3:
		{
			parser.PrintValuteId();
			int id1, money1, id2;
			cout << "ID from:\n>";
			cin >> id1;
			cout << "Money in " << parser.GetValuteName(id1) << ":\n>";
			cin >> money1;
			cout << "ID to:\n>";
			cin >> id2;
			cout << "Money in " << parser.GetValuteName(id2) << ":\n>";
			cout  << parser.ConvertFromTo(ValuteParser::VALUTE_TYPES(id1), ValuteParser::VALUTE_TYPES(id2), money1) << endl;
			system("pause");
		}
		break;
		case 4:
		{
			parser.ParseLinks();
			parser.SortLinks();
			parser.PrintLinks();
			parser.SaveLinks("links.txt");
			//system("pause");
		}
		break;
		}

	} while (menu != 5 && menu != -1);

	parser.DBSave("DB.txt");

	if(menu != -1)
		system("pause");
	return 0;
}