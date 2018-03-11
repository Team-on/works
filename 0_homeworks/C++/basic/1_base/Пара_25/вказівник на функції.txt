#include <iostream>
#include <ctime>

#define usi unsigned short int
using std::cin;
using std::cout;
using std::swap;
const char endl = '\n';
const char tab = '\t';
const char s = ' ';

template <typename T>
bool Even(T a){
	return a % 2 == 0 && a != 0;
}
template <typename T>
bool Odd(T a){
	return a % 2;
}
template <typename T>
void print(T *arr, const usi size, bool (*p)(int) = NULL){
	if (p == NULL)
		for (usi i = 0; i < size; i++)
			cout << arr[i] << s;
	else
		for (usi i = 0; i < size; i++)
			if (p(arr[i]))
				cout << arr[i] << s;
	cout << endl;
}
template <typename T>
double Min(T *arr, const usi size){
	T min = arr[0];
	for (usi i = 0; i < size; i++)
	if (min > arr[i])
		min = arr[i];
	return min;
}
template <typename T>
double Max(T *arr, const usi size){
	T max = arr[0];
	for (usi i = 0; i < size; i++)
	if (max < arr[i])
		max = arr[i];
	return max;
}
template <typename T>
double Average(T *arr, const usi size){
	double avg = 0;
	for (usi i = 0; i < size; i++)
		avg += arr[i];
	return avg / size;
}

template <typename T>
double Action(T *arr, const usi size, double(*p)(int *, const usi) = NULL){
	if (p == NULL){
		cout << "Err in Action. p == NULL" << endl;
		return 0;
	}
	return p(arr, size);
}

int main(){
	setlocale(0, "RUS");
	srand(time(0));
	const usi size = 10;
	int arr[size];
	for (usi i = 0; i < size; i++)
		arr[i] = rand() % 9 + 1;

	//void(*pFP)(int *, const usi, bool(int)) = print;

	double(*pF)(int *, const usi, double(int *, const usi)) = NULL;
	pF = Action;
	usi menu;
	do{
		print(arr, size);
		cout << "[1] min" << endl;
		cout << "[2] max" << endl;
		cout << "[3] avg" << endl;
		cout << "[4] Lambda" << endl;
		cout << "[0] exit" << endl;
		cin >> menu;
		switch (menu){
		case 1:
			cout << pF(arr, size, Min);
		break;
		case 2:
			cout << pF(arr, size, Max);
		break;
		case 3:
			cout << pF(arr, size, Average);
		break;
		case 4:
			cout << pF(arr, size, [](int *arr, const usi size) -> double
			{
				int sum = 0;
				for (usi i = 0; i < size; i++)
					sum += arr[i];
				return sum;
			}
			);
			break;
		}
		cout << endl;
	} while (menu != 0);

	return 0;
}

