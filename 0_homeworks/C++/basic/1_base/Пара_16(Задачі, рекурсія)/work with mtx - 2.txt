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
void Sort(T arr[][size], int size);

template <typename T>
int IsSort(T arr[][size], int size);
template <typename T>
int IsSortRev(T arr[][size], int size);

template <typename T>
void RowSum(T arr[][size], int size);

int main(){
	setlocale(0, "RUS");
	srand(time(0));

	
	int arr[size][size];

	Fill(arr, size);
	//Sort(arr, size);
	Print(arr, size);
	RowSum(arr, size);
	


	return 0;
}

template <typename T>
void Fill(T arr[][size], int size){
	for (int i = 0; i < size * size; i++){
		arr[0][i] = rand() % 2;
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

template <typename T>
int IsSort(T arr[][size], int size){
	int cntData = 0, cntRow = 0;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size - 1; j++){
			if (arr[i][j] <= arr[i][j + 1])
				cntData++;
		}
		if (cntData == size - 1)
			cntRow++;
		cntData = 0;
	}

	return cntRow;
}

template <typename T>
int IsSortRev(T arr[][size], int size){
	int cntData = 0, cntRow = 0;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size - 1; j++){
			if (arr[i][j] >= arr[i][j + 1])
				cntData++;
		}
		if (cntData == size - 1)
			cntRow++;
		cntData = 0;
	}

	return cntRow;
}

template <typename T>
void RowSum(T arr[][size], int size){
	int sumCur, sumMin[2] = { 0 }, sumMax[2] = { 0 };

		for (int j = 0; j < size; j++){
			sumMin[0] += arr[0][j];
			sumMax[0] += arr[0][j];
		}

	for (int i = 1; i < size; i++){
		sumCur = 0;
		for (int j = 0; j < size; j++){
			sumCur += arr[i][j];
		}

		cout << "Row: " << i << " Sum: " << sumCur << endl;

		if (sumCur >= sumMax[0]){
			sumMax[0] = sumCur;
			sumMax[1] = i;
		}
		if (sumCur <= sumMin[0]){
			sumMin[0] = sumCur;
			sumMin[1] = i;
		}
	}

	cout << endl;
	cout << "Max: " << sumMax[0] << " Row: " << sumMax[1] << endl;
	cout << "Min: " << sumMin[0] << " Row: " << sumMin[1] << endl;
}