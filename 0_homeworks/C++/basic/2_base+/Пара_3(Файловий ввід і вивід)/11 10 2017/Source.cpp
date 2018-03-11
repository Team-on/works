#include <iostream>
#include <fstream>

using namespace std;

#define usi unsigned short int








int main(int argc, char * argv[]) {
	//--------------------------OUTPUT-----------------------
	/*cout << "argv[0]: " << argv[0] << endl;
	argv[0];

	ofstream fout;
	char filename[] = "MyFile.txt";
	char *fileWithPath = new char[100];
	strcpy(fileWithPath, argv[0]);
	cout << "fileWithPath: " << fileWithPath << endl;

	char *pos = strstr(fileWithPath, "\\");
	pos = '\0';

	cout << "fileWithPath after pos: " << fileWithPath << endl;
	strcat(fileWithPath, filename);
	cout << "fileWithPath after strcat: " << fileWithPath << endl;

	fout.open(fileWithPath, ios_base::out, ios_base::trunc);

	if (!fout.is_open()) {
		cout << "ERROR" << endl;
		return -1;
	}


	int mtx[5][5];

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++)
			fout << (mtx[i][j] = rand() % 9 + 1) << ends;
		fout << endl;
	}

	fout.close();
	cout << "Done!" << endl;
	system("pause");*/

	//----------------------------------------------INPUT--------------------------
	//cout << "argv[0]: " << argv[0] << endl;

	setlocale(0, "RUS");
	ifstream fin;
	ofstream fout;

	char filenameIn[] = "kob.txt";
	char filenameOut[] = "Out.txt";
	
	cin >> filenameIn;

	fout.open(filenameOut);

	if (!fout.is_open()) {
		cout << "ERROR" << endl;
		system("pause");
		return -1;
	}

	for (char c = 'à'; c <= 'ÿ'; c++) {
		long long cnt = 0;
		char tmp;
		fin.open(filenameIn);
		if (!fin.is_open()) {
			cout << "ERROR" << endl;
			system("pause");
			return -1;
		}
		for (int i = 0; fin.peek() != EOF; i++) {
			fin.get(tmp);
			if (tmp == c) {
				cnt++;
			}
		} 
		fout << c << ": " << cnt << endl;
		fin.close();
	}

	fout << endl;
	for (char c = 'À'; c <= 'ß'; c++) {
		long long cnt = 0;
		char tmp;
		fin.open(filenameIn);
		if (!fin.is_open()) {
			cout << "ERROR" << endl;
			system("pause");
			return -1;
		}
		for (int i = 0; fin.peek() != EOF; i++) {
			fin.get(tmp);
			if (tmp == c) {
				cnt++;
			}
		}
		fout << c << ": " << cnt << endl;
		fin.close();
	}

	fout << endl;
	for (char c = '0'; c <= '9'; c++) {
		int cnt = 0;
		char tmp;
		fin.open(filenameIn);
		if (!fin.is_open()) {
			cout << "ERROR" << endl;
			system("pause");
			return -1;
		}
		for (int i = 0; fin.peek() != EOF; i++) {
			fin.get(tmp);
			if (tmp == c) {
				cnt++;
			}
		}
		if (cnt != 0)
			fout << c << ": " << cnt << endl;
		fin.close();
	}
	
	fout << endl;
	for (char c = ' '; c <= ' '; c++) {
		int cnt = 0;
		char tmp;
		fin.open(filenameIn);
		if (!fin.is_open()) {
			cout << "ERROR" << endl;
			system("pause");
			return -1;
		}
		for (int i = 0; fin.peek() != EOF; i++) {
			fin.get(tmp);
			if (tmp == c) {
				cnt++;
			}
		}
		if (cnt != 0)
			fout << c << ": " << cnt << endl;
		fin.close();
	}

	fout.close();
	cout << endl << "Done!" << endl;
	system("pause");


	//---------------------------------------------
	//ofstream fout;
	//char str[_MAX_PATH];   //260
	//strcpy(str, argv[0]);
	//char *p = strstr(str, "11 10 2017.exe");
	//strcpy(p, "file.txt");
	//fout.open(str, ios_base::out, ios_base::trunc);

	//cout << str << endl;

	//system("pause");

	return 0;
}