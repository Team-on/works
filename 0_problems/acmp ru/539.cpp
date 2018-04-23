#include <iostream>
using namespace std;

int main() {
	int tmp;
	cin >> tmp;
	if (tmp != 1)
		cout << ((tmp % 2 == 0) ? tmp / 2 : tmp);
	else
		cout << 0;
	//system("pause");
	return 0;
}