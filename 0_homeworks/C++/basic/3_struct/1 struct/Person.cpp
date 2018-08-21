#include <iostream>

using std::cout;
using std::cin;
using std::endl;
const char s = ' ';
const char tab = '\t';
#define usi unsigned short int

struct Date{
	usi day;
	usi month;
	usi year;
};

struct Person{
private:
	char name[40];
	float height;
	usi age;
	Date birthday;

public:
	Person(char name[40], float height, usi age, Date birthday){
		strcpy(this->name, name);
		this->height = height;
		this->age = age;
		this->birthday.day = birthday.day;
		this->birthday.month = birthday.month;
		this->birthday.year = birthday.year;
	}

	void showPerson(){
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Height: " << height << endl;
		cout << "Birthday day: " << birthday.day << endl;
		cout << "Birthday month: " << birthday.month << endl;
		cout << "Birthday year: " << birthday.year << endl;
	}

};

void main(){
	Person a = { "Tim", 20, 180, { 02, 10, 2001 } };
	a.showPerson();




}