#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::swap;
const char s = ' ';
const char tab = '\t';
#define usi unsigned short int

union MyUnion
{
	int x;
	float y;
};

struct Person{
//private:
	char firstName[20];
	char secondName[20];
	char phoneNumber[14];

//public:
	Person(char firstName[20], char secondName[20], char phoneNumber[14]){
		strcpy(this->firstName, firstName);
		strcpy(this->secondName, secondName);
		strcpy(this->phoneNumber, phoneNumber);
	}
	Person(){
	}
	void ShowPerson(){
		cout  << firstName << tab;
		cout  << secondName << tab;
		cout  << phoneNumber << endl << endl;

	}
	void FillPerson(){
		cout << "First Name: ";
		cin >> firstName;
		cout << "Second Name: ";
		cin >> secondName;
		cout << "Phone Number: ";
		cin >> phoneNumber;
	}
};



template <typename T>
void ArrCreate(T *&a, const int size);
template <typename T>
void ArrDelete(T *&a);
template <typename T>
void ArrDelete(T *&a, usi &size);
template <typename T>
void ArrPushBack(T *&a, usi &size);
template <typename T>
void ArrDeleteByIndex(T *&a, usi &size, const usi &index);

int FindPersonByFirstName(Person *&a, const usi size, char *s);
int FindPersonBySecondName (Person *&a, const usi size, char *s);
int FindPersonByPhone (Person *&a, const usi size, char *s);

void SortPerson(Person *&p, usi &size);

void main(){
	usi sizeContacts = 0;
	Person *contacts = NULL;
	
	MyUnion p;
	p.x = 300;
	cout << p.x << endl;
	cout << p.y << endl;

	
	system("pause");

	usi menu;
	do{
		cout << "[1] - Add contact" << endl;
		cout << "[2] - Print contacts" << endl;
		cout << "[3] - Delete contact" << endl;
		cout << "[4] - Find contact" << endl;
		cout << "[0] - Exit" << endl;
		cin >> menu;
		system("cls");

		usi prevPos = 0;
		switch (menu){
			int pos;
			char s[20];
			usi inMenu;
			

		case 1:
			ArrPushBack(contacts, sizeContacts);
			contacts[sizeContacts - 1].FillPerson();
		break;
		case 2:
			SortPerson(contacts, sizeContacts);
			for (usi i = 0; i < sizeContacts; i++)
				contacts[i].ShowPerson();
		break;
		case 3:
			for (usi i = 0; i < sizeContacts; i++){
				cout << i + 1 << " ";
				contacts[i].ShowPerson();
			}
			cout << "Input pos: ";
			cin >> pos;
			--pos;
			ArrDeleteByIndex(contacts, sizeContacts, pos);
		break;
		case 4:
			cout << "[1] - by name" << endl;
			cout << "[2] - by second name" << endl;
			cout << "[3] - by phone" << endl;
			cin >> inMenu;

			switch (inMenu){	
			case 1:
				cout << "Input name: ";
				cin >> s;
				prevPos = sizeContacts;
				do{
					pos = FindPersonByFirstName(contacts,  prevPos, s);
					if (pos != -1)
						contacts[pos].ShowPerson();
					else
						break;
					prevPos = pos;
				} while (1);
				cout << endl << "Thats all" << endl;
			break;
			case 2:
				cout << "Input second name: ";
				cin >> s;
				do{
					pos = FindPersonBySecondName(contacts, sizeContacts - prevPos, s);
					prevPos = pos;
					if (pos != -1)
						contacts[pos].ShowPerson();
					else
						break;
				} while (1);
				cout << endl << "Thats all" << endl;
			break;
			case 3:
				cout << "Input phone number: ";
				cin >> s;
				do{
					pos = FindPersonByPhone(contacts, sizeContacts - prevPos, s);
					if (pos != -1)
						contacts[pos].ShowPerson();
					else
						break;
					prevPos = pos;
				} while (1);
				cout << endl << "Thats all" << endl;
			break;
			}
			cout << endl;
		break;
		}
	} while (menu != 0);



	ArrDelete(contacts);
}

template <typename T>
void ArrCreate(T *&a, const int size) {
	if (a != NULL) {
		cout << "ERROR in CreateArr! Array adress is not NULL" << endl;
		return;
	}
	if (size <= 0) {
		cout << "ERROR in CreateArr! size <= 0" << endl;
		return;
	}
	a = new T[size];
}
template <typename T>
void ArrDelete(T *&a) {
	if (a == NULL) {
		cout << "ERROR in DeleteArr! Array adress is NULL" << endl;
		return;
	}
	delete[] a;
	a = NULL;
}
template <typename T>
void ArrDelete(T *&a, usi &size) {
	if (a == NULL) {
		cout << "Warning in DeleteArr! Array adress is NULL" << endl;
		return;
	}
	delete[] a;
	a = NULL;
	size = NULL;
}
template <typename T>
void ArrPushBack(T *&a, usi &size){
	T *tmp = new T[size + 1];
	for (usi i = 0; i < size; i++)
		tmp[i] = a[i];
	if (size != NULL)
		ArrDelete(a);
	a = tmp;
	size++;
}
template <typename T>
void ArrDeleteByIndex(T *&a, usi &size,const usi &index){
	if (size == 0)
		return;
	if (size <= index)
		return;

	T *tmp = new T[size - 1];
	for (usi i = 0; i < size; i++){
		if (i < index)
			tmp[i] = a[i];
		else if (i > index)
			tmp[i - 1] = a[i];
	}
	if (size != NULL)
		ArrDelete(a);
	a = tmp;
	size--;
}

int FindPersonByFirstName(Person *&a, const usi size, char *s){
	int pos = -1;
	for (usi i = 0; i < size; i++){
		if (strcmp(a[i].firstName, s) == 0){
			pos = i;
		}
	}
	return pos;
}
int FindPersonBySecondName(Person *&a, const usi size, char *s){
	int pos = -1;
	for (usi i = 0; i < size; i++){
		if (strcmp(a[i].secondName, s) == 0){
			pos = i;
			return pos;
		}
	}
	return pos;
}
int FindPersonByPhone(Person *&a, const usi size, char *s){
	int pos = -1;
	for (usi i = 0; i < size; i++){
		if (strcmp(a[i].phoneNumber, s) == 0){
			pos = i;
			return pos;
		}
	}
	return pos;
}

void SortPerson(Person *&p, usi &size){
	for (usi i = 0; i < size; i++){
		for (usi j = 0; j < size; j++){
			if (strcmp(p[j].firstName, p[j + 1].secondName) == 1)
				swap(p[j], p[j + 1]);
		}
	}
}