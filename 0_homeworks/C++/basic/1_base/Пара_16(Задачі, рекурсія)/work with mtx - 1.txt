#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

const int size = 5;

template <typename T>
void Fill(T arr[][size], int size);
template <typename T>
void Print(T arr[][size], int size);
template <typename T>
void Sort(T arr[][size], int size);;


int main(){
	setlocale(0, "RUS");
	srand(time(0));

	
	int arr[size][size];

	Fill(arr, size);
	Print(arr, size);

	Sort(arr, size);
	Print(arr, size);


	return 0;
}

template <typename T>
void Fill(T arr[][size], int size){
	for (int i = 0; i < size * size; i++){
		arr[0][i] = rand() % 40 + 1;
	}
}

template <typename T>
void Print(T arr[][size], int size){
	for (int i = 0; i < size * size; i++){
		cout << setw(4) << arr[0][i] << " ";
		if (i % size == size - 1 && i != 0)
			cout << endl;
	}
	cout << endl;
}

template <typename T>
void Sort(T arr[][size], int size){
	for (int i = 0; i < size * size - 1; i++){
		int min = i;
		for (int j = i + 1; j < size * size; j++)
		if (arr[0][min] > arr[0][j])
			min = j;

		if (arr[0][min] < arr[0][i])
			swap(arr[0][min], arr[0][i]);

	}
}

