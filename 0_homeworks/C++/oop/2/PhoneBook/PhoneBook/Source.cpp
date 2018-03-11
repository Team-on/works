#include <iostream>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <string.h>
#include <conio.h>
#include <limits>
using namespace std;

/*
Создайте приложение "Телефонная книга". 
Необходимо хранить данные об абоненте 
(ФИО													+
домашний телефон,										+
рабочий телефон											+
мобильный телефон,										+
дополнительная информация о контакте)					+

внутри соответствующего клас-
са. Наполните класс переменными-членами, функция-
ми-членами, конструкторами, inline-функциями-членами,
используйте инициализаторы, реализуйте деструктор.
Обязательно необходимо выделять динамически память
под ФИО. 

Предоставьте пользователю возможность:
добавлять новых абонентов								+
удалять абонентов										+
искать абонентов по ФИО
показывать всех абонентов								+
сохранять информацию в файл и загружать из файла.		+
*/

class Abonent{
private:
	char **data;
	bool sex;
	long long int *number;
	static int spaceCnt;
public:
	enum e_date{NAME, SURNAME, FATHET_NAME, STREET, ADD_INFO, DATA_CNT};
	enum e_number{ MOBILE, HOME, WORK, NUMBER_CNT };

	Abonent(){
		data = new char*[DATA_CNT];
		for (int i = 0; i < DATA_CNT; i++)
			data[i] = nullptr;
		number = new long long int[NUMBER_CNT];
		for (int i = 0; i < NUMBER_CNT; i++)
			number[i] = 0;
	}
	~Abonent(){
		for (int i = 0; i < DATA_CNT; i++) {
			if (data[i] != nullptr)
				delete[] data[i];
		}
		delete[] data;
		delete[] number;
	}

	void BDRead(ifstream &fin){
		for (int i = 0; i < DATA_CNT; i++){
			char tmp[200];
			fin.getline(tmp, 200);
			SetE_date(e_date(i), tmp);
		}
		for (int i = 0; i < NUMBER_CNT; i++){
			long long int tmp;
			fin >> tmp;
			SetE_number(e_number(i), tmp);
		}
		fin >> sex;
		fin.ignore();
		fin.ignore();
	}
	void BDSave(ofstream &fout) const {
		for (int i = 0; i < DATA_CNT; i++)
			fout << data[i] << endl;
		for (int i = 0; i < NUMBER_CNT; i++)
			fout << number[i] << endl;
		fout << sex << endl << endl;
	}

	void SetE_date(e_date type, char *dataNEW) {
		if (type >= 0 && type < DATA_CNT) {
			if(data[type] != nullptr)
				delete[] data[type];
			data[type] = new char[strlen(dataNEW) + 1];
			strcpy(data[type], dataNEW);
		}
	}
	void SetE_number(e_number type, long long int numberNEW) {
		if (type >= 0 && type < NUMBER_CNT)
			number[type] = numberNEW;
	}
	void GetInput() {
		char tmp[200];
		for (int i = 0; i < DATA_CNT; i++) {
			switch (i){
			case 0:
				cout << "NAME: ";
			break;
			case 1:
				cout << "SURNAME: ";
				break;
			case 2:
				cout << "FATHET_NAME: ";
				break;
			case 3:
				cout << "STREET: ";
				break;
			case 4:
				cout << "ADD_INFO: ";
			}
			cin.getline(tmp, 200);
			SetE_date(e_date(i), tmp);
		}
		for (int i = 0; i < NUMBER_CNT; i++) {
			switch (i){
			case 0:
				cout << "MOBILE: ";
				break;
			case 1:
				cout << "HOME: ";
				break;
			case 2:
				cout << "WORK: ";
			}
			cin.getline(tmp, 200);
			SetE_number(e_number(i), atoll(tmp));
		}
		cout << "SEX(1 - male, 0 - female): ";
		cin >> sex;
	}

	char *GetE_date(e_date type){
		if(type >= 0 && type < DATA_CNT) {
			if (data[type] != nullptr){
				return data[type];
			}
		}
	}
	long long GetE_number(e_number type){
		if (type >= 0 && type < NUMBER_CNT) {
			if (data[type] != nullptr){
				return number[type];
			}
		}
	}
	bool GetSex(){
		return sex;
	}

	void Copy(Abonent &newAb){
		for (int i = 0; i < DATA_CNT; i++){
			this->SetE_date(e_date(i), newAb.data[i]);
		}
		for (int i = 0; i < NUMBER_CNT; i++){
			this->SetE_number(e_number(i), newAb.number[i]);
		}
		sex = newAb.sex;
	}

	static void PrintHeader()  {
		cout << setw(3) << "ID" << " | ";
		cout << setw(spaceCnt) << "SEX" << " | ";
		cout << setw(spaceCnt) << "NAME" << " | ";
		cout << setw(spaceCnt) << "SURNAME" << " | ";
		cout << setw(spaceCnt) << "PATRONYMIC" << " | ";
		cout << setw(spaceCnt) << "STREET" << " | ";
		cout << setw(spaceCnt + 3) << "MOBILE" << " | ";
		cout << setw(spaceCnt + 3) << "HOME" << " | ";
		cout << setw(spaceCnt + 3) << "WORK" << " | ";
		cout << setw(spaceCnt) << "ADD_INFO";
		cout << endl << "---------------------------------------------------------------------------------------------------------------------------------------";
	}
	void Print() const {
		cout << setw(spaceCnt) << ((sex == 1) ? "Male" : "Female") << " | ";
		for (int i = 0; i < DATA_CNT - 1; i++)
			cout << setw(spaceCnt) << data[i] << " | ";
		for (int i = 0; i < NUMBER_CNT; i++)
			cout << setw(spaceCnt + 3) << number[i] << " | ";
		cout << data[DATA_CNT - 1];
	}
};

class PhoneBook{
private:
	unsigned int sizeCurr;
	unsigned int sizeMax;
	Abonent *book;
	char PATH_TO_BD[_MAX_PATH];
public:
	PhoneBook() : PhoneBook(""){ }
	PhoneBook(char newPATH[]) {
		strcpy(PATH_TO_BD, newPATH);
		book = new Abonent[25];
		sizeCurr = 0;
		sizeMax = 25;
		if (PATH_TO_BD != '\0')
			BDRead();
	}
	~PhoneBook(){
		if(book != nullptr)
			delete[] book;
	}

	void SetPath(char newPATH[]){
		if (newPATH != nullptr)
			strcpy(PATH_TO_BD, newPATH);
	}
	
	void BDRead(){
		ifstream fin(PATH_TO_BD);
		if (fin.is_open()) {
			fin >> sizeCurr;
			fin.ignore();
			sizeMax = sizeCurr;
			book = new Abonent[sizeCurr];
			for (int i = 0; i < sizeCurr; i++)
				book[i].BDRead(fin);
			fin.close();
		}
		else {
			cout << "ERROR! Cant open for read " << PATH_TO_BD << endl;
			cout << "Try to create it" << endl;
			ofstream fout(PATH_TO_BD);
			fout.close();
		}
	}
	void BDSave() const {
		ofstream fout(PATH_TO_BD);
			if (fout.is_open()) {
			fout << sizeCurr << endl;
			for (int i = 0; i < sizeCurr; i++)
				book[i].BDSave(fout);
			fout.close();
		}
		else 
			cout << "ERROR! Cant open for write " << PATH_TO_BD << endl;
	}

	void Print() const {
		for (int i = 0; i < sizeCurr; i++) {
			cout << setw(3) << i << " | ";
			book[i].Print();
			cout << endl;
		}
	}

	void Find(Abonent::e_date type, char strF[]){
		Abonent::PrintHeader();
		cout << endl;
		if (strF[strlen(strF) - 1] == '*'){
			strF[strlen(strF) - 1] = '\0';
			for (int i = 0; i < sizeCurr; i++) {
				char *p = strstr(book[i].GetE_date(type), strF);
				if (p) {
					cout << setw(3) << i << " | ";
					book[i].Print();
					cout << endl;
				}
			}
		}
		else{
			for (int i = 0; i < sizeCurr; i++){
				if (strcmp(book[i].GetE_date(type), strF) == 0){
					cout << setw(3) << i << " | ";
					book[i].Print();
					cout << endl;
				}
			}
		}
	}
	void Find(Abonent::e_number type, char strF[]){
		Abonent::PrintHeader();
		cout << endl;
		int curr;
		curr = atol(strF);
		if (strF[strlen(strF) - 1] == '*'){
			strF[strlen(strF) - 1] = '\0';
			char curr[100];
			for (int i = 0; i < sizeCurr; i++) {
				ltoa(book[i].GetE_number(type), curr, 10);
				char *p = strstr(curr, strF);
				if (p) {
					cout << setw(3) << i << " | ";
					book[i].Print();
					cout << endl;
				}
			}
		}
		else{
			for (int i = 0; i < sizeCurr; i++){
				if (curr == book[i].GetE_number(type)){
					cout << setw(3) << i << " | ";
					book[i].Print();
					cout << endl;
				}
			}
		}
	}
	void Find(char strF[]){
		bool gender = 0;
		gender = atoi(strF);
		if (strF[strlen(strF) - 1] == '*'){
			Print();
		}
		else{
			Abonent::PrintHeader();
			cout << endl;
			for (int i = 0; i < sizeCurr; i++){
				if (gender == book[i].GetSex()){
					cout << setw(3) << i << " | ";
					book[i].Print();
					cout << endl;
				}
			}
		}
	}

	void PushBack(Abonent *&newAbonent){
		if (sizeMax < sizeCurr + 1) {
			Abonent *tmp = new Abonent[sizeMax + 25];
			sizeMax += 25;
			for (int i = 0; i < sizeCurr; i++) 
				tmp[i].Copy(book[i]);
			delete[] book;
			book = tmp;
		}
		book[sizeCurr++] = *newAbonent;
	}
	void DeleteByIndex(const int index){
		if ((index >= 0 && index < sizeCurr) &&
			sizeCurr != 0
			){
			if (index == sizeCurr - 1)
				sizeCurr--;
			else{
				Abonent *tmp = new Abonent[sizeMax];
				for (int i = 0; i < sizeCurr; i++){
					if (i < index)
						tmp[i].Copy(book[i]);
					else if (i > index){
						tmp[i - 1].Copy(book[i]);
					}
				}
				delete[] book;
				book = tmp;
				sizeCurr--;
			}
		}
	}
	void ChangeByIndex(const int index, Abonent::e_date type, char dataNEW[]){
		if ((index >= 0 && index < sizeCurr) &&
			sizeCurr != 0
			){
			book[index].SetE_date(type, dataNEW);
			
		}
	}
	void ChangeByIndex(const int index, Abonent::e_number type, long long numberNEW){
		if ((index >= 0 && index < sizeCurr) &&
			sizeCurr != 0
			){
			book[index].SetE_number(type, numberNEW);

		}
	}
};

int Abonent::spaceCnt = 10;

char *FindLast(char str[], const char symbol = '\\', const bool returnNext = 1) {
	for (int i = strlen(str) - 1 - returnNext; i >= 0; i--) {
		if (str[i] == symbol) {
			return &str[i + returnNext];
		}
	}
	return nullptr;
}
void pause() {
	system("pause");
}

int main(int argc, char *argv[]){
	{
		//Console pos
		HWND hwnd;
		SetConsoleTitle("PhoneBook");
		hwnd = FindWindow(NULL, "PhoneBook");
		MoveWindow(hwnd, 0, 0, 200, 200, TRUE);

		HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD maxWindow = GetLargestConsoleWindowSize(out_handle); 
		SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 4, maxWindow.Y - 3};
		SetConsoleScreenBufferSize(out_handle, maxWindow);
		SetConsoleWindowInfo(out_handle, true, &srctWindow);
	}

	char PATH[_MAX_PATH];
	strcpy(PATH, argv[0]);
	char *p = FindLast(PATH);
	strcpy(p, "base.BD");

	PhoneBook book(PATH);

	char mainMenu;

	do{
		cout << "[a] - Add abonent" << endl;
		cout << "[d] - Del abonent" << endl;
		cout << "[f] - Find abonent" << endl;
		cout << "[c] - Change abonent" << endl;
		cout << "[s] - Show book" << endl;
		cout << "[0] - Exit" << endl;
		mainMenu = getch();
		system("cls");
		mainMenu = tolower(mainMenu);

		switch (mainMenu){
		case '?':
			cout << "[a] - Add abonent" << endl;
			cout << "[d] - Del abonent" << endl;
			cout << "[f] - Find abonent" << endl;
			cout << "[c] - Change abonent" << endl;
			cout << "[s] - Show book" << endl;
			cout << "[0] - Exit" << endl;
		break;
		case 'f':
			int type;
			char str[200];
			cout << "WHATS TO FIND: " << endl;
			cout << "[0] - NAME" << endl;
			cout << "[1] - SURNAME" << endl;
			cout << "[2] - FATHET_NAME" << endl;
			cout << "[3] - STREET" << endl;
			cout << "[4] - ADD_INFO" << endl;
			cout << "[5] - MOBILE NUMBER" << endl;
			cout << "[6] - HOME NUMBER" << endl;
			cout << "[7] - WORK NUMBER" << endl;
			cout << "[8] - SEX" << endl;
			cin >> type;
			cin.ignore();
			cout << "FIND DATA(* - all): ";
			cin.getline(str, 200);
			if (type < Abonent::DATA_CNT)
				book.Find(Abonent::e_date(type), str);
			else if (type != 8)
				book.Find(Abonent::e_number(type - Abonent::DATA_CNT), str);
			else
				book.Find(str);
		break;
		case 'a':
		{
			Abonent *newab = new Abonent;
			newab->GetInput();
			cin.ignore();
			book.PushBack(newab);
		}
		break;
		case 's':
			Abonent::PrintHeader();
			cout << endl;
			book.Print();
			cout << endl;
		break;
		case 'd':
		{
			int index;
			cout << "ID: ";
			cin >> index;
			book.DeleteByIndex(index);
		}
		break;
		case 'c':
		{
			int index, type;
			char str[200];
			cout << "ID: ";
			cin >> index;
			cout << "WHATS TO CHANGE: " << endl;
			cout << "[0] - NAME" << endl;
			cout << "[1] - SURNAME" << endl;
			cout << "[2] - FATHET_NAME" << endl;
			cout << "[3] - STREET" << endl;
			cout << "[4] - ADD_INFO" << endl;
			cout << "[5] - MOBILE NUMBER" << endl;
			cout << "[6] - HOME NUMBER" << endl;
			cout << "[7] - WORK NUMBER" << endl;
			cin >> type;
			cin.ignore();
			cout << "NEW DATA: ";
			cin.getline(str, 200);
			if (type < Abonent::DATA_CNT)
				book.ChangeByIndex(index,Abonent::e_date(type), str);
			else
				book.ChangeByIndex(index, Abonent::e_number(type - Abonent::DATA_CNT), atoll(str));
		}
		break;
		}
		cout << endl;
	} while (mainMenu != '0');


	book.BDSave();

	atexit(pause);
	return 0;
}