#include "Header.h"

using namespace std;





const int matrix_size_row = 5;
const int matrix_size_data = 5;



template <typename T>
int Binary_search(T arr[], T find);

template <typename T>
void Matrix_fill(T arr[matrix_size_row][matrix_size_data]);

template <typename T>
void Matix_printl(T arr[matrix_size_row][matrix_size_data]);

template <typename T>
void Matix_sum_diagonal_down(T arr[matrix_size_row][matrix_size_data]);

template <typename T>
void Matix_sum_diagonal_up(T arr[matrix_size_row][matrix_size_data]);

template <typename T>
void Matix_sum_krai(T arr[matrix_size_row][matrix_size_data]);

template <typename T>
int Factorial(T n);

template <typename T>
int Fibonachi(T f){
	if (f == 1)
		return 0;
	if (f == 2)
		return 1;
	return Fibonachi(f - 1) + Fibonachi(f - 2);
}

template <typename T>
int Fibonachi_tri(T f){
	if (f == 1)
		return 0;
	if (f == 2)
		return 0;
	if (f == 3)
		return 1;
	return Fibonachi_tri(f - 1) + Fibonachi_tri(f - 2) + +Fibonachi_tri(f - 3);
}

int main(){

	/*int arr[matrix_size_row][matrix_size_data];

	Matrix_fill(arr);
	Matix_printl(arr);

	Matix_sum_diagonal_down(arr);
	cout << endl;
	Matix_sum_diagonal_up(arr);
	cout << endl;
	Matix_sum_krai(arr);*/

	int x, n;
	cin >> n;
	x = Fibonachi_tri(n);
	cout << x << endl;


	return 0;
}






template <typename T>
int Factorial(T n){
	return (n == 1 || n == 0)? 1 : Factorial(n - 1) ;
}


template <typename T>
int Binary_search(T arr[], T find, int arr_size){
	int pos;
	int l = 0, r = arr_size - 1, m = (l + r) / 2;

	while (1){
		if (arr[m] > find)
			r = m - 1;
		if (arr[m] < find)
			l = m + 1;
		if (arr[m] == find){
			pos = m;
			break;
		}
		m = (l + r) / 2;
	}
	return pos;
}

template <typename T>
void Matrix_fill(T arr[matrix_size_row][matrix_size_data]){
	for (int i = 0; i < matrix_size_row; i++){
		for (int j = 0; j < matrix_size_data; j++){
			arr[i][j] = rand() % 10;
		}
	}
}

template <typename T>
void Matix_printl(T arr[matrix_size_row][matrix_size_data]){
	for (int i = 0; i < matrix_size_row; i++){
		for (int j = 0; j < matrix_size_data; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

template <typename T>
void Matix_sum_diagonal_down(T arr[matrix_size_row][matrix_size_data]){
	int sum = 0;
	for (int i = 0; i < matrix_size_row; i++){
		for (int j = 0; j < matrix_size_data; j++){
			if (i > j){
				sum += arr[i][j];
				cout << arr[i][j] << " ";
			}
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << "Sum is " << sum << endl;
}

template <typename T>
void Matix_sum_diagonal_up(T arr[matrix_size_row][matrix_size_data]){
	int sum = 0;
	for (int i = 0; i < matrix_size_row; i++){
		for (int j = 0; j < matrix_size_data; j++){
			if (i < j){
				sum += arr[i][j];
				cout << arr[i][j] << " ";
			}
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << "Sum is " << sum << endl;
}

template <typename T>
void Matix_sum_krai(T arr[matrix_size_row][matrix_size_data]){
	int sum = 0;
	for (int i = 0; i < matrix_size_row; i++){
		for (int j = 0; j < matrix_size_data; j++){
			if (i == matrix_size_row - 1 || j == matrix_size_data - 1 || i == 0 || j == 0){
				sum += arr[i][j];
				cout << arr[i][j] << " ";
			}
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << "Sum is " << sum << endl;
}





