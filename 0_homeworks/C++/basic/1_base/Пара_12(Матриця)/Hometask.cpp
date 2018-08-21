#include <iostream>								//Оголошення інших бібліотек
#include <ctime>

using namespace std;

//-----------------------------------------------------------------------------------------

void	fill(long[]);						//Заповнення
void	Arr_printl(long[], long[]);			//Друк массиву і нова лінія в кінці
int		Arr_find_linear(long[], long);		// Лінійний пошук
void	Arr_sort_vubor(long[], long[]);		//Сортування

void	Matrix_print(int[]);
//-----------------------------------------------------------------------------------------

	const int Arr_size = 10;
	const int mtx_size = 4;

//----------------------------------------------------------------------------------


	void main() {
		srand(time(0));
		long isq[Arr_size], number[Arr_size];
		int menu;

		fill(isq);
		fill(number);

		cout << "\t\t\tPhone Book" << endl;
	menu:

		cout << "[1] - phone book" << endl;
		cout << "[2] - sort by ISQ" << endl;
		cout << "[3] - sort by phone number" << endl;
		cout << "[4] - exit" << endl;
		cout << "[5] - DZ second part" << endl;
		cin >> menu;

		switch (menu) {
		case 1:
			Arr_printl(isq, number);
			goto menu;
		case 2:
			Arr_sort_vubor(isq, number);
			cout << "\nDone!\n";
			goto menu;
		case 3:
			Arr_sort_vubor(number, isq);
			cout << "\nDone!\n";
			goto menu;
		case 4:
			goto exit;
		case 5:
			goto DZ_2;
		default:
			goto menu;
		}

	DZ_2:
		cout << "\t\t\tMatrix shift" << endl;

		int shift, matrix[mtx_size][mtx_size];

		for (int i = 0; i < mtx_size; i++) {
			for (int j = 0; j < mtx_size; j++) {
				matrix[i][j] = rand() % 10;
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}

	DZ_2_menu:

		cout << "[1] - shift up" << endl;
		cout << "[2] - shift down" << endl;
		cout << "[3] - shift left" << endl;
		cout << "[4] - shift right" << endl;
		cout << "[5] - exit" << endl;
		cout << "[6] - DZ first part" << endl;
		cin >> shift;

		switch (shift) {
		case 1:
			for (int i = mtx_size - 1; i >= 1; i--) {
				int tmp[mtx_size];
				for (int j = 0; j < mtx_size; j++){
					swap(matrix[i][j], matrix[0][j]);
				}
			}

			for (int i = 0; i < mtx_size; i++) {
				for (int j = 0; j < mtx_size; j++)
					cout << matrix[i][j] << " ";
				cout << endl;
			}
			goto DZ_2_menu;
		case 2:
			for (int i = 1; i < mtx_size; i++) {
				int tmp[mtx_size];
				for (int j = 0; j < mtx_size; j++) {
					swap(matrix[i][j], matrix[0][j]);
				}
			}

			for (int i = 0; i < mtx_size; i++) {
				for (int j = 0; j < mtx_size; j++)
					cout << matrix[i][j] << " ";
				cout << endl;
			}
			goto DZ_2_menu;
		case 3:
			for (int i = 0; i < mtx_size; i++) {
				int tmp[mtx_size];
				for (int j = mtx_size - 1; j >= 1; j--) {
					swap(matrix[i][0], matrix[i][j]);
				}
			}

			for (int i = 0; i < mtx_size; i++) {
				for (int j = 0; j < mtx_size; j++)
					cout << matrix[i][j] << " ";
				cout << endl;
			}
			goto DZ_2_menu;
		case 4:
			for (int i = 0; i < mtx_size; i++) {
				int tmp[mtx_size];
				for (int j = 1; j < mtx_size; j++) {
					swap(matrix[i][0], matrix[i][j]);
				}
			}

			for (int i = 0; i < mtx_size; i++) {
				for (int j = 0; j < mtx_size; j++)
					cout << matrix[i][j] << " ";
				cout << endl;
			}
			goto DZ_2_menu;
		case 5:
			goto exit;
		case 6:
			goto menu;
		default:
			goto DZ_2_menu;
		}



	exit:;
}


void fill(long isq[]) {
	for (int i = 0; i < Arr_size; i++) {
		isq[i] = (rand() % 99999 + 10000) * 10000 + (rand() % 99999 + 99999) * 1000 + rand() % 100;
	}
}

int		Arr_find_linear(long a[], long num) {
	for (int i = 0; i < Arr_size; i++)
		if (a[i] == num)
			return i;
	return -1;
}

void	Arr_printl(long a[], long b[]) {
	cout << "ISQ\t\tPhone Number" << endl;
	for (int i = 0; i < Arr_size; i++) {
		int n1 = a[i] / 1000000;
		int n2 = a[i] / 1000 % 1000;
		int n3 = a[i] % 1000;

		if (n1 < 10)
			n1 *= 100;
		else if (n1 < 100)
			n1 *= 10;

		if (n2 < 10)
			n2 *= 100;
		else if (n2 < 100)
			n2 *= 10;

		if (n3 < 10)
			n3 *= 100;
		else if (n3 < 100)
			n3 *= 10;

		cout << n1 << " - " << n2 << " - " << n3 << "\t\t" << "+380 (" << b[i] / 10000000 << ") " << b[i] % 10000000   << endl;
	}
	cout << endl << endl;
}

void	Arr_sort_vubor(long arr[], long arr2[]) {
	long min, min2;

	for (int i = 0; i < Arr_size - 1; i++) {
		min = i;

		for (int j = i + 1; j < Arr_size; j++) {
			if (arr[min] > arr[j])
				min = j;
		}

		if (min != i){
			swap(arr[min], arr[i]);
			swap(arr2[min], arr2[i]);
		}
	}
}

/*
1) Написать программу «справочник». Создать два одномерных массива. Один массив хранит
номера ICQ, второй – телефонные номера. Реализовать меню для пользователя:
- Отсортировать по номерам ICQ
- Отсортировать по номерам телефона
- Вывести список пользователей
- Поиск по номеру ICQ
- Выход
(Якщо сортується один масив то разом з ним повинен змінюватися і інший. Меню організувати з допомогою оператора switch)
2) Зробити зсув елементів матриці вверх, та вниз
*/