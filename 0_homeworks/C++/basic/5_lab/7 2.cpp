#include <iostream>
#include <algorithm>
#include <math.h>

using std::cout;
using std::endl;

using std::abs;

//7.2
/*inline*/ void print(const double &a) noexcept {
	cout << a << endl;
}

/*inline*/ void print(double * const &a, const char s) noexcept {
	if (a == nullptr)
		return;

	std::for_each(a, a + s, [](const double &c) {cout << c << ' '; });
	cout << endl;
}

void main() {
	unsigned char size, i, cnt, min, max;
	double *arr, sum, avg, mul;

	//1
	size = 6;
	arr = new double[size] {5, -2.3, -6.9, -1.1, 2, 6.6};

	for (i = 0, sum = 0; i < size; ++i)
		if (arr[i] > 0)
			sum += arr[i];

	print(sum);

	delete[] arr;

	//2
	size = 8;
	arr = new double[size] {-6.3, -1, 10.3, -8.8, 6.3, -1.1, 0, 0.1};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] > 0 && i % 2 == 0)
			++cnt;

	print(cnt);

	delete[] arr;

	//3
	size = 6;
	arr = new double[size] {6.3, 2.1, 4.2, 5.3, -7.2, -4.5};

	for (i = 0, avg = 0, cnt = 0; i < size; ++i)
		if (arr[i] < 0) {
			++cnt;
			avg += arr[i];
		}
	avg /= cnt;

	print(avg);

	delete[] arr;

	//4
	size = 7;
	arr = new double[size] {6.3, -1.6, 1.1, 0.1, -2, 2.3, 6.3};

	for (i = 1, min = 0; i < size; ++i)
		if (arr[min] > arr[i])
			min = i;

	print(arr[min]);

	delete[] arr;

	//5
	size = 12;
	arr = new double[size] {-2.3, 4, -8.9, 6.3, 4.9, -7.8, -6.5, 5.1, 3.8, -4.3, -5.1, 7.2};

	for (i = 0, sum = 0; i < size; ++i)
		if (arr[i] < 0 && i % 2 == 0)
			sum += arr[i];

	print(sum);

	delete[] arr;

	//6
	size = 10;
	arr = new double[size] {6.3, 0, -8.3, 7.2, 6.1, -4.2, 5.7, 6.4, 5.6, -4.8};

	for (i = 0, avg = 0, cnt = 0; i < size; ++i)
		if (arr[i] >= 0 && i % 2) {
			++cnt;
			avg += arr[i];
		}
	avg /= cnt;

	print(avg);

	delete[] arr;

	//7
	size = 9;
	arr = new double[size] {1.6, 2.1, -3.1, 0, 1.1, -2.2, 3.7, 8.9, 9.2};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] > 0)
			++cnt;

	print(cnt);

	delete[] arr;

	//8
	size = 5;
	arr = new double[size] {1.1, -6.2, 0, 2.3, 5.1};

	for (i = 0, mul = 1; i < size; ++i)
		if (arr[i] > 0)
			mul *= arr[i];

	print(mul);

	delete[] arr;

	//9
	size = 6;
	arr = new double[size] {3.5, -6.3, 2.1, 0.1, 5.1, -2.1};

	for (i = 0, sum = 0; i < size; ++i)
		if (arr[i] < 0.25)
			sum += arr[i];

	print(sum);

	delete[] arr;

	//10
	size = 7;
	arr = new double[size] {-2.2, 0.2, 3.1, 2.1, -3.1, 6.1, 0.5};

	for (i = 0, mul = 1; i < size; ++i)
		mul *= abs(arr[i]);

	print(mul);

	delete[] arr;

	//11
	size = 5;
	arr = new double[size] {2.2, 3.1, -3.6, 0.1, 2.1};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] < 0.99)
			++cnt;

	print(cnt);

	delete[] arr;

	//12
	size = 5;
	arr = new double[size] {1.2, 25.3, -2.3, -3.1, 0};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] < 0)
			++cnt;

	print(cnt);

	delete[] arr;

	//13
	size = 6;
	arr = new double[size] {2.3, 4.3, -15.2, 1.2, -1.2, -3.3};

	for (i = 0, mul = 1; i < size; ++i)
		if (arr[i] > 2)
			mul *= arr[i];

	print(mul);

	delete[] arr;

	//14
	size = 8;
	arr = new double[size] {-7.9, 1, 1.1, -2.2, 5, -1.1, 2};

	for (i = 0; i < size; ++i)
		if (arr[i] < 0)
			cout << arr[i] << ' ';
	cout << endl;

	delete[] arr;

	//15
	size = 6;
	arr = new double[size] { 2.1, 3.6, -6.3, 4.1, 2.2, -2.3};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] > 2.3)
			++cnt;

	print(cnt);

	delete[] arr;

	//16
	size = 5;
	arr = new double[size] {3.1, -7.8, 6.2, -3.3, 1.1};

	for (i = 0, mul = 1; i < size; ++i)
		if (arr[i] > -5.4)
			mul *= arr[i];

	print(mul);

	delete[] arr;

	//17
	size = 8;
	arr = new double[size] {-1.2, 6.3, 0.2, -0.7, 1.1, 2.3, -3.6, 2.2};

	for (i = 0, sum = 0; i < size; ++i)
		if (arr[i] < 0)
			sum += arr[i];

	print(sum);

	delete[] arr;

	//18
	size = 7;
	arr = new double[size] {1.1, 2.3, -6.4, 0, 2.1, 2.3, 1.2};

	std::for_each(arr, arr + size, [](const double &c) {
		if (c > 0)
			cout << c << ' ';
	});
	cout << endl;

	delete[] arr;

	//19
	size = 5;
	arr = new double[size] {1.3, 6.3, 2.4, -3.6, -2.5};

	for (i = 0, mul = 1; i < size; ++i)
		mul *= arr[i];

	print(mul);

	delete[] arr;

	//20
	size = 6;
	arr = new double[size] {2.1, -3.6, -2, 0, -6.3, 1};

	for (i = 1, min = 0; i < size; ++i)
		if (arr[min] > arr[i])
			min = i;

	cout << static_cast<unsigned short>(min) << ' ' << arr[min] << endl;

	delete[] arr;

	//21
	size = 8;
	arr = new double[size] {3.2, -6.3, 2, -3.3, -6.6, -2.2, 0, 2.1};

	for (i = 0; i < size; ++i)
		if (arr[i] < 0) {
			cout << static_cast<unsigned short>(i) << endl;
			break;
		}

	delete[] arr;

	//22
	size = 6;
	arr = new double[size] {2.3, 7.9, 12.3, -6.8, -22.3, 0};

	for (i = 1, max = 0; i < size; ++i)
		if (arr[max] < arr[i])
			max = i;

	cout << static_cast<unsigned short>(max) << ' ' << arr[max] << endl;

	delete[] arr;

	//23
	size = 7;
	arr = new double[size] {2.2, -3.3, 2.1, -3, -7.1, -5.1, 0};

	for (i = 0; i < size; ++i)
		if (arr[i] < 0)
			cout << static_cast<unsigned short>(i) << ' ';
	cout << endl;

	delete[] arr;

	//24
	size = 6;
	arr = new double[size] {21.3, 30.5, -6.8, 0.3, -1.2, 5.3};

	for (i = 1, min = 0; i < size; ++i)
		if (arr[min] > arr[i])
			min = i;

	print(arr[min]);

	delete[] arr;

	//25
	size = 8;
	arr = new double[size] {-3.6, -5.3, 2.1, 0.1, -0.7, 5.3, 6.6, -2.2};

	for (i = 1, max = 0; i < size; ++i)
		if (abs(arr[max]) < abs(arr[i]))
			max = i;

	print(arr[max]);

	delete[] arr;

	//26
	size = 7;
	arr = new double[size] {-2.3, 2.3, 0, 3.2, 6, -6, 3.2};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] >= 0)
			++cnt;

	print(cnt);

	delete[] arr;

	//27
	size = 8;
	arr = new double[size] {6.3, 26, -3.6, 2.1, 0, 6.6, -7.2, 1.1};

	for (i = 0, cnt = 0; i < size; ++i)
		if (abs(arr[i]) < 5)
			++cnt;

	print(cnt);

	delete[] arr;

	//28
	size = 5;
	arr = new double[size] {3.2, 6.3, -3.3, 2.3, 5.5};

	for (i = 0, avg = 0, cnt = 0; i < size; ++i) {
		++cnt;
		avg += arr[i];
	}
	avg /= cnt;

	print(avg);

	delete[] arr;

	//29
	size = 6;
	arr = new double[size] {6.2, -3.2, 0, 3.3, 2.2, -3.6};

	for (i = 0, cnt = 0; i < size; ++i)
		if (arr[i] > 0)
			++cnt;

	print(cnt);

	delete[] arr;

	//30
	size = 6;
	arr = new double[size] {3.3, 0, -3.3, -6.16, 6.6, 2.1};

	for (i = 1, max = 0; i < size; ++i)
		if (arr[max] < arr[i])
			max = i;

	print(arr[max]);

	delete[] arr;
}