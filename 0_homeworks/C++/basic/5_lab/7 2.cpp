#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

//7.2
void print(const double &a) {
	cout << a << endl;
}

void print(double * const &a, const char s) {
	if (a == nullptr)
		return;

	for (double *i = a, *end = a + s; i <= end; ++i)
		cout << *i << ' ';
	//for_each(a, a + s, [](const double &c) {cout << c << ' '; });
	cout << endl;
}

void main() {
	unsigned char size, i, cnt, min, max;
	double *arr, sum, avg, mul;

	//7
	size = 9;
	arr = new double[size] {1.6, 2.1, -3.1, 0, 1.1, -2.2, 3.7, 8.9, 9.2};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] > 0)
			++cnt;

	print(cnt);

	delete[] arr;
}