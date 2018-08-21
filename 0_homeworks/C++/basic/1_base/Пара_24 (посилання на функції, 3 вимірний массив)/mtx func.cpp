#include <iostream>
#include <ctime>
#include <iomanip>

#define usi unsigned short int
using std::cin;
using std::cout;
using std::swap;
using std::setw;
const char endl = '\n';
const char tab = '\t';
const char s = ' ';

template <typename T>
void MtxDFill(T **& p, const usi &row, const usi &col);
template <typename T>
void MtxDPrint(T **& p, const usi &row, const usi &col);

template <typename T>
void MtxDCreate(T **& p, usi row, usi col);
template <typename T>
void MtxDDelete(T **& p, usi &row, usi &col);

template <typename T>
void MtxDDelColNBest(T **& p, const usi &row, usi &col, const usi &N);
template <typename T>
void MtxDAddColNBest(T **& p, const usi &row, usi &col, const usi &N);

template <typename T>
void MtxDAddColSum(T **& p, const usi &row, usi &col);
template <typename T>
void MtxDAddRowSum(T **& p, usi &row, usi &col);


template <typename T>
void MtxDAddRowNBest(T **& p, usi &row, const usi &col, const usi &N);

int main() {
	srand(time(0));

	usi row, col;
	int ** p = NULL;

	cout << "Row: ";
	cin >> row;
	cout << "Col: ";
	cin >> col;

	MtxDCreate(p, row, col);
	MtxDFill(p, row, col);
	MtxDPrint(p, row, col);

	usi menu;
	do {
		usi posCol;
		cout << "[1] - Add col" << endl;
		cout << "[2] - Del col" << endl;
		cout << "[3] - Add row" << endl;
		cout << "[4] - Del row" << endl;
		cout << "[5] - col sum" << endl;
		cout << "[6] - row sum" << endl;
		cout << "[0] - Exit" << endl;
		cin >> menu;
		cin.ignore();
		if (menu && menu != 5 && menu != 6) {
			if (menu == 1 || menu == 2)
				cout << "Input col pos: ";
			if (menu == 3 || menu == 4)
				cout << "Input row pos: ";
			cin >> posCol;
		}
		switch (menu) {
		case 1:
			MtxDAddColNBest(p, row, col, posCol);
		break;
		case 2:
			MtxDDelColNBest(p, row, col, posCol);
		break;
		case 3:
			MtxDAddRowNBest(p, row, col, posCol);
		break;
		case 4:
			MtxDAddRowNBest(p, row, col, posCol);
			break;
		case 5:
			MtxDAddColSum(p, row, col);
			break;
		case 6:
			MtxDAddRowSum(p, row, col);
			break;
		}
		if (menu)
			MtxDPrint(p, row, col);
	} while (menu);


	MtxDDelete(p, row, col);
	return 0;
}

template <typename T>
void MtxDAddColSum(T **& p, const usi &row, usi &col){
	usi N = col;
	if (N > col) {
		cout << "ERROR! N > col" << endl;
		return;
	}

	T * tmp = NULL;

	for (usi i = 0; i < row; i++) {
		tmp = new T[col + 1];
		int RowSum = 0;
		for (usi j = 0; j < col; j++)
			RowSum += p[i][j];
		tmp[N] = RowSum;
		for (usi j = 0; j < col + 1; j++) {
			if (j < N)
				tmp[j] = p[i][j];
			else
				tmp[j + 1] = p[i][j];
		}
		delete[] p[i];
		p[i] = tmp;
	}

	++col;
}
template <typename T>
void MtxDAddRowSum(T **& p, usi &row, usi &col){
	T ** tmp = new T *[row + 1];

	for (usi i = 0; i < row; i++) {
		tmp[i] = new T[col];
		tmp[i] = p[i];
	}

	tmp[row] = new T[col];
	for (usi i = 0; i < col; i++){
		int colSum = 0;
		for (usi j = 0; j < row; j++)
			colSum += p[j][i];
		tmp[row][i] = colSum;
	}

	delete[] p;
	p = new T*[row + 1];
	p = tmp;

	++row;
}

template <typename T>
void MtxDFill(T **& p, const usi &row, const usi &col) {
	for (usi i = 0; i < row; i++)
	for (usi j = 0; j < col; j++)
		p[i][j] = rand() % 10;
}
template <typename T>
void MtxDPrint(T **& p, const usi &row, const usi &col) {
	for (usi i = 0; i < row; i++) {
		for (usi j = 0; j < col; j++)
			cout << setw(4) << p[i][j];
		cout << endl;
	}
	cout << endl;
}

template <typename T>
void MtxDCreate(T **& p, usi row, usi col) {
	p = new int *[row];
	for (usi i = 0; i < row; i++)
		p[i] = new int[col];
}
template <typename T>
void MtxDDelete(T **& p, usi &row, usi &col) {
	for (usi i = 0; i < row; i++)
		delete[] p[i];
	delete[] p;
	row = col = 0;
}

template <typename T>
void MtxDDelColNBest(T **& p, const usi &row, usi &col, const usi &N) {
	if (0 == col) {
		cout << "ERROR! 0 == col" << endl;
		return;
	}
	if (N >= col) {
		cout << "ERROR! N > col" << endl;
		return;
	}

	T * tmp = NULL;

	for (usi i = 0; i < row; i++) {
		tmp = new T[col - 1];
		for (usi j = 0; j < col; j++) {
			if (j < N)
				tmp[j] = p[i][j];
			else if (j > N)
				tmp[j - 1] = p[i][j];
		}
		delete[] p[i];
		p[i] = tmp;
	}

	--col;
}
template <typename T>
void MtxDAddColNBest(T **& p, const usi &row, usi &col, const usi &N) {
	if (N > col) {
		cout << "ERROR! N > col" << endl;
		return;
	}

	T * tmp = NULL;

	for (usi i = 0; i < row; i++) {
		tmp = new T[col + 1];
		tmp[N] = 0;
		for (usi j = 0; j < col + 1; j++) {
			if (j < N)
				tmp[j] = p[i][j];
			else
				tmp[j + 1] = p[i][j];
		}
		delete[] p[i];
		p[i] = tmp;
	}

	++col;
}

//Не робе. Пофіксити як в MtxDAddRowSum
template <typename T>
void MtxDAddRowNBest(T **& p, usi &row, const usi &col, const usi &N) {
	if (N > col) {
		cout << "ERROR! N > col" << endl;
		return;
	}

	T ** tmp = new T * [row + 1];

	tmp[N] = new T[col];
	for (usi i = 0; i < col; i++)
		tmp[N][i] = 0;

	for (usi i = 0; i < row; i++) {
			if (i < N)
				tmp[i] = p[i];
			else
				tmp[i + 1] = p[i];
	}

	for (usi i = 0; i < row + 1; i++)
		p[i] = tmp[i];

	++row;
}