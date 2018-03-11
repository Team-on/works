#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct STR1{
	char baa;
	char b;
	char ba;
	double a;	
	double aa;
	double aaa;
};

struct STR2{
	char baa;
	double a;
	char ba;
	double aa;
	char b;
	double aaa;
};

void main(){
	cout << sizeof(STR1) << endl;
	cout << sizeof(STR2) << endl;
}