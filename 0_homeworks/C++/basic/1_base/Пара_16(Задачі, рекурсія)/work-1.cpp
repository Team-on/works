#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
int BinarySearchRec(T arr[], int num, int l, int r);
template <typename T1, typename T2>
int BinarySearchRec(T1 arr[], T2 num, T2 l, T2 r);
template <typename T>
int BinarySearchWhile(T arr[], int num, int size);
template <typename T1, typename T2>
int BinarySearchWhile(T1 arr[], T2 num, T2 size);

template <typename T>
void Fill(T arr[], int size);
template <typename T>
void Print(T arr[], int size);
template <typename T>
void Sort(T arr[], int size);;


int main(){
	setlocale(0, "RUS");
	srand(time(0));

	const int size = 10;
	int arr[size], n;

	Fill(arr, size);
	Sort(arr, size);
	Print(arr, size);

	cout << "Number: ";
	cin >> n;
	n = BinarySearchRec(arr, n, 0, size);
	cout << "Pos: " << n << endl;

	cout << "Number: ";
	cin >> n;
	n = BinarySearchWhile(arr, n, size);
	cout << "Pos: " << n << endl;

	return 0;
}

template <typename T>
void Fill(T arr[], int size){
	for (int i = 0; i < size; i++){
		arr[i] = rand() % 40 + 1;
	}
}

template <typename T>
void Print(T arr[], int size){
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

template <typename T>
void Sort(T arr[], int size){
	for (int i = 0; i < size - 1; i++){
		int min = i;
		for (int j = i + 1; j < size; j++)
		if (arr[min] > arr[j])
			min = j;

		if (arr[min] < arr[i])
			swap(arr[min], arr[i]);

	}
}

template <typename T>
int BinarySearchRec(T arr[], int num, int l, int r){
	if (l > r)
		return -1;

	int m = (l + r) / 2;
	if(arr[m] == num)
		return m;
	if (arr[m] < num)
		return BinarySearchRec(arr, num, m + 1, r);
	if (arr[m] > num)
		return BinarySearchRec(arr, num, l, m - 1);
}

template <typename T>
int BinarySearchWhile(T arr[], int num, int size){
	int l = 0, r = size, m;

	while (l <= r){
		m = (l + r) / 2;
		if (arr[m] == num)
			return m;
		else if (arr[m] < num)
			l = m + 1;
		else if (arr[m] > num)
			r = m - 1;
	}
		return -1;
}

template <typename T1, typename T2>
int BinarySearchRec(T1 arr[], T2 num, T2 l, T2 r) {
	if (l > r)
		return -1;

	T2 m = (l + r) / 2;
	if (arr[m] == num)
		return m;
	if (arr[m] < num)
		return BinarySearchRec(arr, num, m + 1, r);
	if (arr[m] > num)
		return BinarySearchRec(arr, num, l, m - 1);
}

template <typename T1, typename T2>
int BinarySearchWhile(T1 arr[], T2 num, T2 size){
	T2 l = 0, r = size, m;

	while (l <= r){
		m = (l + r) / 2;
		if (arr[m] == num)
			return m;
		else if (arr[m] < num)
			l = m + 1;
		else if (arr[m] > num)
			r = m - 1;
	}
	return -1;
}
