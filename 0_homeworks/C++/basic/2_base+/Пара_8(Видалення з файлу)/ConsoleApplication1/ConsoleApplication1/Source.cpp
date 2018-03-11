#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int

int main(int argc, char * argv[]) {
	setlocale(0, "RUS");
	ofstream fout;
	ifstream fin;
	const char PRJ_NAME[] = "ConsoleApplication1.exe";
	const char OUTPUT_NAME[] = "in.txt";
	const char INPUT_NAME[] = "in.txt";
	char PATH[_MAX_PATH];   //260
	strcpy(PATH, argv[0]);
	char *p = strstr(PATH, PRJ_NAME);
	strcpy(p, INPUT_NAME);



	usi menu;
	
	do {
		cout << "Завдання: ";
		cin >> menu;
		switch (menu) {
		case 1:
		{
			strcpy(p, INPUT_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}
			usi cnt = 0;
			char f;
			cout << "Лiтера: ";
			cin >> f;
			char ch[2];

			ch[0] = fin.get();
			if (ch[0] == f)
				cnt++;
			for (; fin.peek() != EOF;) {
				ch[1] = fin.get();
				if (ch[1] == f && (ch[0] == ' ' || ch[0] == '\n'))
					cnt++;
				ch[0] = ch[1];
			}
			cout << "Found " << cnt << " words" << endl;

			fin.close();
		}
		break;
		case 2:
		{
			strcpy(p, INPUT_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}

			usi cntC, cntNL;
			cntC = cntNL = 0;
			for (; fin.peek() != EOF;) {
				char ch = fin.get();
				if (isalpha(ch) || isalnum(ch))
					++cntC;
				if (ch == '\n')
					++cntNL;
			}
			//if (fin.peek() == EOF)
				++cntNL;

			cout << "Found " << cntC << " chars" << endl;
			cout << "Found " << cntNL << " lines" << endl;

			fin.close();

		}
		break;
		case 3:
		{
			const char CENSOR_NAME[] = "cens.txt";
			strcpy(p, CENSOR_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}

			usi WORD_CNT = 1;
			for (; fin.peek() != EOF;) {
				char ch = fin.get();
				if (ch == ' ' || ch == '\n')
					++WORD_CNT;
			}
			fin.seekg(0);
			char **word = new char*[WORD_CNT + 1];
			for(usi i = 0; i < WORD_CNT + 1; i++)
				word[i] = new char[32];

			for (usi i = 0; i < WORD_CNT; i++) {
				fin >> word[i];
				//int length = strlen(word[i]);
				//word[i][length] = ' ';
				//word[i][length + 1] = '\0';
			}
			fin.close();

			strcpy(p, INPUT_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}
			unsigned long long FILE_LENGTH = 0;
			for (FILE_LENGTH = 0; fin.peek() != EOF; FILE_LENGTH++) {
				fin.get();
			}
			fin.seekg(0);
			char *text = new char[FILE_LENGTH + 1];
			for (unsigned long long i = 0; fin.peek() != EOF; i++) {
				text[i] = fin.get();
			}
			text[FILE_LENGTH] = '\0';
			fin.close();
			cout << text << endl;

			for (usi i = 0; i < WORD_CNT; i++) {
				cout << "Try to delete " <<   word[i] << endl;
				while (char *p = strstr(text, word[i])) {
					for (usi j = 0; j < strlen(p); j++) {
						//cout << j << "/" << strlen(word[i]) << endl;
						p[j] = p[strlen(word[i]) + j];
					}
				}
				//cout << "Delete all " << word[i] << endl;
			}
			cout << text << endl << endl;
			
			strcpy(p, OUTPUT_NAME);
			fout.open(PATH);
			if (!fout.is_open()) {
				cout << "Cant open " << OUTPUT_NAME << endl;
				system("pause");
				return -1;
			}
			fout << text;
			fout.close();

			for (usi i = 0; i < WORD_CNT; i++)
				delete[] word[i];
			delete[] word;
		}
		break;
		case 4:
		{
			const char CENSOR_NAME[] = "cens.txt";
			strcpy(p, CENSOR_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}

			usi WORD_CNT = 1;
			for (; fin.peek() != EOF;) {
				char ch = fin.get();
				if (ch == ' ' || ch == '\n')
					++WORD_CNT;
			}
			fin.seekg(0);
			char **word = new char*[WORD_CNT + 1];
			for (usi i = 0; i < WORD_CNT + 1; i++)
				word[i] = new char[32];

			for (usi i = 0; i < WORD_CNT; i++) {
				fin >> word[i];
				int length = strlen(word[i]);
				word[i][length] = ' ';
				word[i][length + 1] = '\0';
			}
			fin.close();

			strcpy(p, INPUT_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}

			strcpy(p, "tmp");
			fout.open(PATH);
			if (!fout.is_open()) {
				cout << "Cant open " << OUTPUT_NAME << endl;
				system("pause");
				return -1;
			}

			for (; fin.peek() != EOF;) {
				char buff[32];
				fin >> buff;
				usi cnt = 0;
				for (usi i = 0; i < WORD_CNT; i++) {
					if (strcmp(buff, word[i]) != 0)
						cnt++;
				}
				if (cnt == WORD_CNT)
					fout << buff;
			}
			fout.close();

			
			fin.close();
			
			strcpy(p, INPUT_NAME);
			fout.open(PATH);
			if (!fout.is_open()) {
				cout << "Cant open " << OUTPUT_NAME << endl;
				system("pause");
				return -1;
			}
			
			strcpy(p, "tmp");
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << INPUT_NAME << endl;
				system("pause");
				return -1;
			}

			for (; fin.peek() != EOF;) {
				char buff[32];
				fin >> buff;
				fout << buff;
			}

			fout.close();
		}
		break;
		}
	} while (menu >= 1 && menu <= 4);


	system("pause");
	return 0;
}
