#include <iostream>
#include <conio.h>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <ctime>
using namespace std;

/*
{
cout << "Введіть числа. Напишіть [All] коли закінчите\n";
char buff[32];
do {
cin >> buff;
if (strstr(buff, "All"))
break;
if (buff[0] < '0' || buff[0] > '9')
continue;
++arr[atoi(buff)];
} while (1);
}
*/


int main() {
	atexit([]() {cout << "\n:END:"; _getch(); });
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	long long int multiple = 1, sum = 0;
	map <int, int> arr;

	{
		long long int size;
		cout << "Size: "; cin >> size;
		do {
			++arr[rand() % 500 + 1];
		} while (size--);
	}

	double endTime, startTime = clock() / 1000;
	for (auto i = arr.cbegin(); i != arr.cend(); ++i) {
		if (i->second == 1)
			multiple *= i->first;
		else
			sum += i->first;
	}
	endTime = clock(); 

	cout << "time " << (endTime - startTime) / 10000 << endl;
	cout << "Sum: " << sum << endl;
	cout << "Multiple: " << multiple;
	return EXIT_SUCCESS;
}