/*
Задача B
Задана послідовність цілих чисел. Кожне число із послідовності не менше за -20`000`000 і не більше за 20000000. Всього у послідовності не більше ніж 40 чисел. 
Послідовність чисел завершується символом «кінець рядка». Виведіть на екран суму усіх чисел.
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	long long a[100], num, aPos = 0, p = 0, sum = 0;

	getline(cin, s);

	//cout << s << endl;

	while (p < s.length()){
		num = 0;

		while (p < s.length() && s[p] != ' ') {
			num *= 10;
			num += s[p] - '0';
			++p;
		}

		a[aPos++] = num;
		++p;
	}

	for (char i = 0; i < aPos; ++i)
		//cout << a[i] << ' ';
		sum += a[i];
	cout << sum;// << endl;

	return 0;
}