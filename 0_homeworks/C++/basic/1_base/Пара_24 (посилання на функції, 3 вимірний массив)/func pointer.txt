#include <iostream>

#define usi unsigned short int
using std::cin;
using std::cout;
const char endl = '\n';
const char tab = '\t';
const char s = ' ';

int sum(int a, int b){
	return a + b;
}

int divv(int a, int b){
	return a / b;
}

int min(int a, int b){
	return a - b;
}

int mul(int a, int b){
	return a * b;
}

int main() {

	int (*ptr[4]) (int, int) = {sum, divv, min, mul};

	for (usi i = 0; i < 4; i++)
		cout << ptr[i](5, 20) << endl;

	return 0;
}
