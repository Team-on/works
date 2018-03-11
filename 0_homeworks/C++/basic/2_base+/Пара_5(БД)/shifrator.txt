#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int

void cryptZhezar(char *s, const usi key) {
	for (usi i = 0; i < strlen(s); i++) {
		if ((s[i] >= 'a' && s[i] <= 'z')) {
			if (s[i] + (key % 26) > 'z')
				s[i] = s[i] - 26 + (key % 26);
			else if (s[i] + (key % 26) < 'a')
				s[i] = s[i] + 26 + (key % 26);
			else
				s[i] += (key % 26);
		}
	}
}
void decryptZhezar(char *s, const usi key) {
	for (usi i = 0; i < strlen(s); i++) {
		if ((s[i] >= 'a' && s[i] <= 'z')) {
			if (s[i] - key > 'z')
				s[i] = s[i] - 26 - (key % 26 + 1);
			else if (s[i] - key < 'a')
				s[i] = s[i] + 26 - (key % 26 + 1);
			else
				s[i] -= key;
		}
	}
}

int main(int argc, char * argv[]) {
	ofstream fout;
	ifstream fin;

	const char PRJ_NAME[] = "ConsoleApplication1.exe";
	const char OUTPUT_NAME[] = "out.txt";
	const char INPUT_NAME[] = "out.txt";

	char PATH[_MAX_PATH];   //260
	strcpy(PATH, argv[0]);
	char *p = strstr(PATH, PRJ_NAME);
	cout << p << endl;
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
		text[i] = fin.get();
	}
	text[FILE_LENGTH] = '\0';
	cout << text << endl;
	
	usi key, menu;
	cin >> menu;
	cin >> key;
	switch (menu) {
	case 1:
		cryptZhezar(text, key);
		break;
	case 2:
		decryptZhezar(text, key);
	}

	strcpy(p, OUTPUT_NAME);
	fout.open(PATH);
	if (!fout.is_open()) {
		cout << "Cant open " << OUTPUT_NAME << endl;
		system("pause");
		return -1;
	}
	cout << text << endl;
	fout << text << endl;

	fout.close();
	fin.close();
	system("pause");
	return 0;
}