#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <ctime>
using namespace std;

#define usi unsigned short int

class Test
{
private:
	int a, b;
public:
	void SetA(int aNew) {
		a = aNew;
	}
	void SetB(int bNew) {
		b = bNew;
	}
	int GetA() {
		return a;
	}
	int GetB() {
		return b;
	}

	void Print() {
		cout << a << ends << b << endl;
	}

	Test(int f = 0, int s = 0) {
		a = f;
		b = s;
	}
	
	int Add() {
		return a + b;
	}
	int Min() {
		return a - b;
	}
	int Mul() {
		return a * b;
	}
	int Div() {
		if(b != 0)
			return a / b;
		return 0;
	}

	Test& operator=(const Test &r) {
		this->a = r.a;
		this->b = r.b;
		return *this;
	}

	Test operator+(const int &r) {
		Test tmp(this->GetA(), this->GetB());
			tmp.a += r;
			tmp.b += r;
			return tmp;
	}

};


int main(int argc, char * argv[]) {
	Test a(20, 10), b(100, 200);
	a = a + 3;
	cout << a.Add() << endl;
	cout << a.Min() << endl;
	cout << a.Mul() << endl;
	cout << a.Div() << endl;

	return 0;
}