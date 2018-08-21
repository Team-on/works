#include <iostream>
#include <windows.h>

#include <bitset>

using std::cin;
using std::cout;
using std::endl;

using namespace std;

#define usi unsigned short int
const char t = '\t';


struct Student{
	char nameNSurname[40];
	bool algebra : 1;
	bool english : 1;
	bool geometry : 1;
	bool fizra : 1;
	bool informatica : 1;
};

struct abs{
	int a, b;
} A = {10, 20};

void main(){
	/*Student Vasya;

		bool *tmp = new bool;

		cout << "Is Student pass algebra?" << endl;
		cin >> *tmp;
		Vasya.algebra = *tmp;
	
		cout << "Is Student pass english?" << endl;
		cin >> *tmp;
		Vasya.english = *tmp;

		cout << "Is Student pass geometry?" << endl;
		cin >> *tmp;<< boolalpha
		Vasya.geometry = *tmp;

		cout << "Is Student pass fizra?" << endl;
		cin >> *tmp;
		Vasya.fizra = *tmp;

		cout << "Is Student pass informatica?" << endl;
		cin >> *tmp;
		Vasya.informatica = *tmp;

		delete tmp;
		cout << endl << endl;

		cout << "algebra:" << t;
		cout << boolalpha << Vasya.algebra << endl;

		cout << "english:" << t;
		cout << Vasya.english << endl;

		cout << "geometry:" << t;
		cout << noboolalpha << Vasya.geometry << endl;

		cout << "fizra:" << t << t;
		cout << Vasya.fizra << endl;

		cout << "informatica:" << t;
		cout << Vasya.informatica << endl;*/

	/*const int size = 15;
	bitset <size> A;
	
	for (usi i = 0; i < pow(2, size); i++){
		A = i;
		cout << A << t;
		cout << A.to_ulong() << endl;
		Sleep(20);
	}*/

	cout << A.a << endl;
	cout << A.b << endl;
}


