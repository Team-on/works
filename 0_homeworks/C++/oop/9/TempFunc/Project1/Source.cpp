#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
void ArrSort(T *arr, int size) {
	for (int i = 0; i < size; ++i) {
		int min = i;
		for (int j = i; j < size; ++j)
			if (arr[min] > arr[j])
				min = j;
		if (min != i)
			swap(arr[min], arr[i]);
	}
}

template <typename T>
int ArrMax(T *arr, int size) {
	int max = 0;
	for (int i = 1; i < size; ++i) 
		if (arr[max] < arr[i])
			max = i;
	return max;
}

template <typename T>
int ArrMin(T *arr, int size) {
	int min = 0;
	for (int i = 1; i < size; ++i)
		if (arr[min] > arr[i])
			min = i;
	return min;
}

template <typename T>
void ArrChange(T *arr, int size, T value, int pos) {
	if (pos < 0 || pos >= size)
		return;
	arr[pos] = value;
}

template <typename T>
bool ArrIsSort(T *arr, int size) {
	for (int i = 1; i < size; ++i)
		if (arr[i - 1] > arr[i])
			return 0;
	return 1;
}

template <typename T>
void ArrPrint(T *arr, int size) {
	for (T *p = arr; p < &arr[size - 1]; ++p)
		cout << *p << ends;
}

template <typename T>
int ArrSearchBin(T *arr, int size, T value, int start = 0) {
	int curr = (size + start) / 2;
	if (size <= start)
		return -1;
	if (arr[curr] < value)
		return ArrSearchBin(arr, size , value, curr + 1);
	if (arr[curr] > value)
		return ArrSearchBin(arr, curr - 1, value, start);
	return curr;
}

template <typename T1, typename T2>
auto f(T1 a, T2 b) //->decltype(a + b)
{
	return a + b;
}

/*
Реализуйте шаблонные функции для поиска максимума,минимума, сортировки массива (любым алгоритмом сортировки), двоичного поиска в массиве, замены элемента массива на переданное значение. 
*/
void main() {
	srand(time(0));
	///*
	const int size = 10;
	int arr[10];
	for (int i = 0; i < size; ++i)
		arr[i] = rand() % 20;
	ArrPrint(arr, size);	cout << endl;
	ArrSort(arr, size);
	ArrPrint(arr, size);	cout << endl;
	int val = 13;
	//cin >> val;
	if (ArrIsSort(arr, size)) {
		int an = ArrSearchBin(arr, size, val);
		if (an != -1)
			cout << arr[an];
		else
			cout << an;
		cout << endl;
	}
	//cout << "Min: " << arr[ArrMin(arr, size)]  << endl;
	//cout << "Max: " << arr[ArrMax(arr, size)] << endl;

	cout << "Min: " << arr[0] << endl;
	cout << "Max: " << arr[size - 1] << endl;

	//*/

	/*
	auto a = 3;
	auto b = 4.5;

	auto k = f(a, b);
	cout << k << ends << typeid(k).name() << endl;
	*/

	system("pause");
}

