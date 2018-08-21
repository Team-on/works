#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int

struct person {
	char *name;
	usi age;

	void show() {
		cout << "Name: " << name ;
		cout << "\tAge: " << age << endl;
	}
};

template <typename T>
void ArrPushBack(T *&arr, usi &size) {
	T *tmp = new T[size + 1];

	for (usi i = 0; i < size; i++)
		tmp[i] = arr[i];
	arr = tmp;
	++size;
}

void PersonFill(person &stydnt) {
	char name[20];
	cout << "Name: ";
	cin >> name;
	stydnt.name = new char[strlen(name)];
	strcpy(stydnt.name, name);
	cout << "Age: ";
	usi age;
	cin >> age;
	stydnt.age = age;
}

void ReadFromBD(person *&stydnt, usi &size, ifstream &fin) {
	usi sizeTMP;
	fin >> sizeTMP;
	for (usi i = 0; i < sizeTMP; i++) {
		ArrPushBack(stydnt, size);
		char name[20];
		fin >> name;
		fin >> name;
		stydnt[i].name = new char[strlen(name)];
		strcpy(stydnt[i].name, name);
		fin >> name;
		fin >> stydnt[i].age;
	}
	size = sizeTMP;
}
void SaveToBD(person *&stydnt, usi &size, ofstream &fout) {
	fout << size << endl;
	for (usi i = 0; i < size; i++) {
		fout << "Name: " << stydnt[i].name << " " << "Age: " << stydnt[i].age << endl;
	}
}

int main(int argc, char * argv[]) {
	
	const char PRJ_NAME[] = "ConsoleApplication1.exe";
	const char BD_NAME[] = "base.txt";
	char PATH[_MAX_PATH];   //260
	strcpy(PATH, argv[0]);
	char *p = strstr(PATH, PRJ_NAME);

	usi size = 0;
	person *stydnt = new person[size];

	ifstream fin;
	strcpy(p, BD_NAME);
	fin.open(PATH);
	if (!fin.is_open()) {
			cout << "Cant open " << BD_NAME << endl;
			system("pause");
			return -1;
		}
	ReadFromBD(stydnt, size, fin);
	fin.close();
	

	usi menu;
	do {
		cout << "[1] - add" << endl;
		cout << "[2] - print" << endl;
		cout << "[0] - exit" << endl;
		do {
			cin >> menu;
		} while (menu <= 0 && menu >= 3);
		system("cls");
		switch (menu) {
		case 1:
			ArrPushBack(stydnt, size);
			PersonFill(stydnt[size - 1]);
			break;
		case 2:
			for (usi i = 0; i < size; i++) {
				stydnt[i].show();
			}
			cout << endl;
		}
	} while (menu != 0);


	ofstream fout;
	strcpy(p, BD_NAME);
	fout.open(PATH);
	if (!fout.is_open()) {
		cout << "Cant open " << BD_NAME << endl;
		system("pause");
		return -1;
	}

	SaveToBD(stydnt, size, fout);
	fout.close();

	system("pause");
	return 0;
}