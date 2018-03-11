#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;
//Не найкраща ідея
typedef unsigned short int usi;

class Date {
public:
	usi day : 5;
	usi mounth : 4;
	usi year;

public:
	void Print() {
		printf("%d/%d/%d", day, mounth, year);
	}
	void Set(const usi day, const usi mounth, const usi year) {
		this->day = day;
		this->mounth = mounth;
		this->year = year;
	}
	bool IsYear366(const usi year) {
		if ((year % 4 == 0 && year % 100 != 0) ||
			(year % 400 == 0))
			return 1;
		else
			return 0;
	}
	usi	 DayInMounth(const usi m, const usi y) {
		usi d = 31;
		if (m == 2)
			d = 28 + int(IsYear366(y));
		if (m == 4 || m == 6 || m == 9 || m == 11)
			d = 30;
		return d;
	}
};

class Student{
private:
	char *name, *surname;
	double lenght;
	char *group;
	Date dateOfBirth;
	int age;
public:
	Student(){
		name = surname = group = nullptr;
		lenght = age = 0;
	}
	Student(char *nm, char *sn, char *gr, double len){
		name = new char[strlen(nm) + 1];
		strcpy(name, nm);
		surname = new char[strlen(sn) + 1];
		strcpy(surname, sn);
		group = new char[strlen(gr) + 1];
		strcpy(group, gr);
		lenght = len;
	}
	~Student(){
		delete[] name;
		delete[] surname;
		delete[] group;
	}

	void SetName(char *nm){
		if (name != nullptr)
			delete[] name;
		name = new char[strlen(nm) + 1];
		strcpy(name, nm);
	}
	void SetSurname(char *sr){
		if (surname != nullptr)
			delete[] surname;
		surname = new char[strlen(sr) + 1];
		strcpy(surname, sr);
	}
	void SetGroup(char *gr){
		if (group != nullptr)
			delete[] group;
		group = new char[strlen(gr) + 1];
		strcpy(group, gr);
	}
	void SetLenght(double len){
		if (len >= 0)
			lenght = len;
	}

	void SetDateCons() {
		cout << "Date of birth ";
		int day_F, mounth, year;      // Чогось з usi не робе. Наверно специфiка scanf();
		cout << " (day/mounth/year): ";
		do {
			scanf("%d/%d/%d", &day_F, &mounth, &year);
		} while (!(
			(1 <= day_F && day_F <= dateOfBirth.DayInMounth(mounth, year)) &&
			(1 <= mounth && mounth <= 12) &&
			(year <= 2000 && year > 0)
			));
		dateOfBirth.Set(day_F, mounth, year);

		time_t timer;
		struct tm y2k = { 0 };
		double seconds;
		y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
		y2k.tm_year = dateOfBirth.year - 1900; y2k.tm_mon = dateOfBirth.mounth - 1; y2k.tm_mday = dateOfBirth.day;
		time(&timer);
		if (mktime(&y2k) != -1) {
			seconds = difftime(timer, mktime(&y2k));
			age = seconds / 3600 / 24 / 365;
		}
		else {  
			age = abs(dateOfBirth.year - 1970 - (timer / 3600 / 24 / 365));
		}
	}

	void Print(){
		char ends = '\t';
		cout << name << ends << surname << ends << group << ends << lenght << ends; dateOfBirth.Print(); cout << ends << ends << age;
	}
	friend void Header();
};
void Header(){
		char ends = '\t';
		cout << "name" << ends << "surname" << ends << "group" << ends << "lenght" << ends << "Date Of Birth" << ends << ends << "Age";
	}

void main(){
	usi size = 2;
	cout << "Size: ";
	cin >> size;
	Student *s = new Student[size];

	for (usi i = 0; i < size; i++){
		char name[50];	double length;
		cout << "Name: ";
		cin.ignore();
		cin.getline(name, 50);
		s[i].SetName(name);
		cout << "Sur: ";
		cin.getline(name, 50);
		s[i].SetSurname(name);
		cout << "Group: ";
		cin.getline(name, 50);
		s[i].SetGroup(name);
		cout << "Len: ";
		cin >> length;
		s[i].SetLenght(length);
		s[i].SetDateCons();
		cout << endl;
	}

	Header();
	cout << endl;
	for (int i = 0; i < size; i++){
		s[i].Print();
		cout << endl;
	}

	delete[] s;
	system("pause");
}