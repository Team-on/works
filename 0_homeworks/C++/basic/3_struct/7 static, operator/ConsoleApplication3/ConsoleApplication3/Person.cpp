#include "Inc.h"
#include "Person.h"

Person::Person() {
	name = surname = NULL;
	age = 0;
	counter++;
}

Person::Person(const Person & prs){
	this->name = new char[strlen(prs.name) + 1];
	this->surname = new char[strlen(prs.surname) + 1];
	strcpy(this->name, prs.name);
	strcpy(this->surname, prs.surname);
	this->age = prs.age;
	counter++;
}

Person::Person(const char * name, const char * surname, const int age){
	this->name = new char [strlen(name) + 1];
	this->surname = new char[strlen(surname) + 1];
	strcpy(this->name, name);
	strcpy(this->surname, surname);
	this->age = age;
	counter++;
}

Person::~Person(){
	delete[] name;
	delete[] surname;
	counter--;
}

void Person::Show(){
	cout << name << ends << surname << endl;
	cout << "Age: " << age << endl;
}

void Person::Rename(const char * name, const char * surname){
	delete[] this->name;
	delete[] this->surname;
	this->name = new char[strlen(name) + 1];
	this->surname = new char[strlen(surname) + 1];
	strcpy(this->name, name);
	strcpy(this->surname, surname);
}

void Person::GetAll(const char * name, const char * surname, const int age_get){
	delete[] this->name;
	delete[] this->surname;
	this->name = new char[strlen(name) + 1];
	this->surname = new char[strlen(surname) + 1];
	strcpy(this->name, name);
	strcpy(this->surname, surname);
	this->age = age_get;
}

void Person::GetCnt() {
	//cout << age << endl;  //ERROR
	cout << counter << endl;
	//this->age;			//ERROR
}

int Person::counter = 0;