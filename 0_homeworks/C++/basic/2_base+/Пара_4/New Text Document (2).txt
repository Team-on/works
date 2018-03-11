#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int

int main(int argc, char * argv[]) {
	setlocale(0, "RUS");
	ofstream fout;
	ifstream fin;

	const char PRJ_NAME[] = "16 10 2017.exe";
	const char OUTPUT_NAME[] = "out.txt";
	const char INPUT_NAME[] = "in.txt";

	char PATH[_MAX_PATH];   //260
	strcpy(PATH, argv[0]);
	char *p = strstr(PATH, PRJ_NAME);
	strcpy(p, OUTPUT_NAME);
	fout.open(PATH);
	strcpy(p, INPUT_NAME);
	fin.open(PATH);

	if (!fout.is_open()) {
		cout << "Cant open " << OUTPUT_NAME << endl;
		system("pause");
		return -1;
	}
	if (!fin.is_open()) {
		cout << "Cant open " << INPUT_NAME << endl;
		system("pause");
		return -1;
	}

	unsigned long long FILE_LENGTH = 0;
	for (FILE_LENGTH = 0; fin.peek() != EOF; FILE_LENGTH++) {
		fin.get();
	}
	cout << FILE_LENGTH << endl;
	fin.seekg(0);
	char *text = new char[FILE_LENGTH];
	for (unsigned long long i = 0; fin.peek() != EOF; i++) {
		text[i] = fin.get();
	}
	text[FILE_LENGTH] = '\0';
	//cout << text << endl;

	char slovo[100], another[100];
	cout << "Zamina: ";
	cin >> slovo;
	cout << "another: ";
	cin >> another;

	while (char *p = strstr(text, slovo)) {
		if (strlen(slovo) == strlen(another)) {
			for (usi i = 0; i < strlen(slovo); i++)
				p[i] = another[i];
		}
		else if (strlen(slovo) > strlen(another)) {
			for (usi i = 0; i < strlen(slovo) - (strlen(slovo) - strlen(another)); i++)
				p[i] = another[i];
			for (usi i = strlen(another); i < strlen(text); i++) {
				cout << i << endl;
				p[i] = p[i + (strlen(slovo) - strlen(another))];
			}
		}

	}
		
	fout << text << endl;

	fout.close();
	fin.close();
	system("pause");
	return 0;
}




//#include <iostream>
//#include <windows.h>
//using namespace std;
//
//int main(int argc, char * argv[]) {
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//
//	cout << "ііі їїї " << endl;
//	system("pause");
//	return 0;
//}



//#include <iostream>
//#include <fstream>
//#include <windows.h>
//using namespace std;
//
//#define usi unsigned short int
//
//int main(int argc, char * argv[]) {
//	ofstream fout;
//	ifstream fin;
//
//	const char PRJ_NAME[] = "16 10 2017.exe";
//	const char OUTPUT_NAME[] = "out.txt";
//	const char INPUT_NAME[] = "in.txt";
//
//	char PATH[_MAX_PATH];   //260
//	strcpy(PATH, argv[0]);
//	char *p = strstr(PATH, PRJ_NAME);
//	strcpy(p, OUTPUT_NAME);
//	fout.open(PATH);
//	strcpy(p, INPUT_NAME);
//	fin.open(PATH);
//	
//	if (!fout.is_open()) {
//		cout << "Cant open " << OUTPUT_NAME << endl;
//		system("pause");
//		return -1;
//	}
//	if (!fin.is_open()) {
//		cout << "Cant open " << INPUT_NAME << endl;
//		system("pause");
//		return -1;
//	}
//
//	for (int i = 0; i < 20; i++) {
//		cout << fin.tellg() << ends;
//		cout << (char)fin.get() << endl;
//		Sleep(20);
//	}
//
//	fin.seekg(10);
//	for (int i = 0; i < 10; i++) {
//		cout << fin.tellg() << ends;
//		cout << (char)fin.get() << endl;
//		Sleep(20);
//	}
//
//	fin.seekg(50, SEEK_SET);
//	for (int i = 0; i < 10; i++) {
//		cout << fin.tellg() << ends;
//		cout << (char)fin.get() << endl;
//		Sleep(20);
//	}
//
//	fin.seekg(50, SEEK_CUR);
//	for (int i = 0; i < 10; i++) {
//		cout << fin.tellg() << ends;
//		cout << (char)fin.get() << endl;
//		Sleep(20);
//	}
//
//	fin.seekg(-50, SEEK_END);
//	for (int i = 0; i < 10; i++) {
//		cout << fin.tellg() << ends;
//		cout << (char)fin.get() << endl;
//		Sleep(20);
//	}
//
//	fout.close();
//	fin.close();
//	system("pause");
//	return 0;
//}


//#include <iostream>
//#include <fstream>
//#include <windows.h>
//using namespace std;
//
//#define usi unsigned short int
//
//int main(int argc, char * argv[]) {
//	setlocale(0, "RUS");
//	ofstream fout;
//	ifstream fin;
//	
//	const char PRJ_NAME[] = "16 10 2017.exe";
//	const char OUTPUT_NAME[] = "game.txt";
//	const char INPUT_NAME[] = "game.txt";
//
//	char PATH[_MAX_PATH];   //260
//	strcpy(PATH, argv[0]);
//	char *p = strstr(PATH, PRJ_NAME);
//
//	strcpy(p, INPUT_NAME);
//	fin.open(PATH);
//	if (!fin.is_open()) {
//		cout << "Cant open " << INPUT_NAME << endl;
//		system("pause");
//		return -1;
//	}
//	
//	int a;
//	fin >> a;
//	fin.close();
//
//	cout << "a = " << a << endl;
//
//	char menu[10];
//	do {
//		cin >> menu;
//		int mod = 0;
//		for (usi i = 1; i < strlen(menu); i++) {
//			mod = mod * 10 + (int(menu[i]) - 48);
//		}
//
//		switch (menu[0]) {
//			case '?':
//				cout << "[+ Число]" << endl;
//				cout << "[- Число]" << endl;
//				cout << "[* Число]" << endl;
//				cout << "[/ Число]" << endl;
//				cout << "[^ Число]" << endl;
//				cout << "s - Повернути до 100" << endl;
//			break;
//			case '+':
//				a += mod;
//			break;
//			case '-':
//				a -= mod;
//			break;
//			case '*':
//				a *= mod;
//			break;
//			case '/': case ':':
//				if (mod != 0)
//					a /= mod;
//				else
//					a = 0;
//			break;
//			case '^':
//				a = pow(a, mod);
//			break;
//			case 's':
//				a = 100;
//			break;
//		}
//		if(menu[0] != '0')
//			cout << "a = " << a << endl;
//
//		strcpy(p, OUTPUT_NAME);
//		fout.open(PATH);
//		if (!fout.is_open()) {
//			cout << "Cant open " << OUTPUT_NAME << endl;
//			system("pause");
//			return -1;
//		}
//		fout << a;
//		fout.close();
//
//	} while (menu[0] != '0');
//
//	system("pause");
//	return 0;
//}