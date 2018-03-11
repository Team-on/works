#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int


bool game(char *word, int &HP) {
	char *cht = new char[strlen(word) + 1];

	for (usi i = 0; i < strlen(word); i++)
		cht[i] = '*';
	cht[strlen(word)] = '\0';
	while (HP) {
		cout << cht << endl;;
		char tmp;
		bool init = 0;
		cin >> tmp;
		for (usi i = 0; i < strlen(word); i++) {
			if (tmp == word[i]) {
				init = 1;
				cht[i] = word[i];
			}
		}
		if (init == 0) {
			--HP;
		}
		init = 1;
		for (usi i = 0; i < strlen(word); i++) 
			if ('*' == cht[i]) 
				init = 0;
		
		if (init == 1) {
			cout << cht << endl;
			HP += 1;
			//cout << "HP: " << HP << endl;

			return 1;
		}
		//cout << "HP: " << HP << endl;
	}
	cout << "You lose!" << endl;
	delete[] cht;
	return 0;
}

int main(int argc, char * argv[]) {
	ifstream fin;
	const char PRJ_NAME[] = "Project1.exe";
	const char INPUT_NAME[] = "in.txt";
	char PATH[_MAX_PATH];   //260
	strcpy(PATH, argv[0]);
	char *p = strstr(PATH, PRJ_NAME);
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
	char *text = new char[FILE_LENGTH];
	for (unsigned long long i = 0; fin.peek() != EOF; i++) {
		if (text[i] == '\0')
			cout << "n" << endl;
		else
			text[i] = fin.get();
	}
	text[FILE_LENGTH] = '\n';
	usi wordCNT = 0;
	for (unsigned long long i = 0; i <= FILE_LENGTH; i++) {
		if (text[i] == '\n')
			++wordCNT;
	}

	char **slova = new char*[wordCNT];
	for (usi i = 0; i < wordCNT; i++)
		slova[i] = new char[32];

	usi jTMP = 0, iTMP = 0;
	for (unsigned long long i = 0; i <= FILE_LENGTH; i++) {
		if (text[i] != '\n') {
			slova[jTMP][iTMP] = text[i];
			++iTMP;
		}
		else {
			slova[jTMP][iTMP] = '\0';
			++jTMP;
			iTMP = 0;
		}

	}


	/*for (unsigned long long i = 0; i < wordCNT; i++) {
		for (unsigned long long j = 0; j < strlen(slova[i]); j++) {
			cout << slova[i][j];
		}
		cout << endl;
	}*/

	int HP = 3;
	for (usi i = 0; game(slova[i], HP) && i < wordCNT - 1; i++) {
		cout << "Next word is: ";
	}
	if(HP)
		cout << "Win!" << endl << "Score: " << HP << endl;



	for(usi i = 0; i < wordCNT; i++)
		delete[] slova[i];
	delete[] slova;
	fin.close();
	system("pause");
	return 0;
}