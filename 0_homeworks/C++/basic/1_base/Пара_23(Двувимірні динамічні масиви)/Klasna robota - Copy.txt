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
void SwapMinMax(T **& p, const usi &row, const usi &col);

template <typename T>
void MtxDFill(T **& p, const usi &row, const usi &col);
template <typename T>
void MtxDPrint(T **& p, const usi &row, const usi &col);

template <typename T>
void MtxDCreate(T **& p, usi row, usi col);
template <typename T>
void MtxDDelete(T **& p, usi &row, usi &col);

template <typename T>
void MtxDAddRow(T **& p, usi &row, const usi &col);
template <typename T>
void MtxDAddCol(T **& p, usi &row, usi &col);

template <typename T>
void MtxDAddRowN(T **& p, usi &row, const usi &col, const usi N);
template <typename T>
void MtxDAddColN(T **& p, usi &row, usi &col, const usi N);

template <typename T>
void MtxDCopyData(T **& source, T **& destination, const usi &row, const usi &col);

int main(){
	srand(time(0));

	/*usi size = 3;
	cin >> size;
	int ** p = new int *[size];
	for (usi i = 0; i < size; i++){
		p[i] = new int [size];
	}

	for (usi i = 0, j = 0; i < size; i += j / (size - 1) ,j++){
		cout << ((j == size) ? endl : s);
		(j == size) ? j = 0 : 0 ;
		p[i][j] = rand () % 10 + 1;
		cout << p[i][j];
	}
	
	for (usi i = 0; i < size; i++)
		delete[] p[i];
	delete[] p;
	*/

	/*usi size;
	cout << "Row: ";
	cin >> size;

	usi *sizes = new usi[size];
	for (usi i = 0; i < size; i++){
		cout << "Col: ";
		cin >> sizes[i];
	}

	int ** p = new int *[size];
	for (usi i = 0; i < size; i++){
		p[i] = new int[sizes[i]];
	}

	for (usi i = 0; i < size; i++)
		for (usi j = 0; j < sizes[i]; j++)
			p[i][j] = rand() % 10;

	for (usi i = 0; i < size; i++){
		for (usi j = 0; j < sizes[i]; j++)
			cout << p[i][j] << s;
		cout << endl;
	}

	for (usi i = 0; i < size; i++)
		delete[] p[i];
	delete[] p;
	delete[] sizes;*/

	usi row, col;
	int ** p = NULL;

	cout << "Row: ";
	cin >> row;
	cout << "Col: ";
	cin >> col;

	MtxDCreate(p, row, col);

	MtxDFill(p, row, col);
	MtxDPrint(p, row, col);

	MtxDAddRowN(p, row, col, 1);
	MtxDPrint(p, row, col);


	MtxDDelete(p, row, col);

	return 0;
}

template <typename T>
void SwapMinMax(T **& p, const usi &row, const usi &col){
	int * pMin = &p[0][0], *pMax = &p[0][0];

	for (usi i = 0; i < row; i++){
		for (usi j = 0; j < col; j++){
			if (p[i][j] < *pMin)
				pMin = &p[i][j];
			if (p[i][j] > *pMax)
				pMax = &p[i][j];
		}
	}

	int tmp = *pMin;
	*pMin = *pMax;
	*pMax = tmp;
}

template <typename T>
void MtxDFill(T **& p, const usi &row, const usi &col){
	for (usi i = 0; i < row; i++)
	for (usi j = 0; j < col; j++)
		p[i][j] = rand() % 10;
}
template <typename T>
void MtxDPrint(T **& p, const usi &row, const usi &col){
	for (usi i = 0; i < row; i++){
		for (usi j = 0; j < col; j++)
			cout << p[i][j] << s;
		cout << endl;
	}
	cout << endl;
}

template <typename T>
void MtxDCreate(T **& p, usi row, usi col){
	p = new int *[row];
	for (usi i = 0; i < row; i++)
		p[i] = new int[col];
}
template <typename T>
void MtxDDelete(T **& p, usi &row, usi &col){
	for (usi i = 0; i < row; i++)
		delete[] p[i];
	delete[] p;
	row = col = 0;
}

template <typename T>
void MtxDAddRow(T **& p, usi &row, const usi &col){
	T ** tmp = new T *[row + 1];
	for (usi i = 0; i < row; i++)
		tmp[i] = p[i];
	delete [] p;
	p = tmp;
	p[row] = new T[col];
	for (usi i = 0; i < col; i++)
		p[row][i] = 0;
	++row;
}

template <typename T>
void MtxDAddCol(T **& p, usi &row, usi &col){
	T ** tmp = NULL;
	MtxDCreate(tmp, row, col + 1);
	MtxDCopyData(p, tmp, row, col);

	for (usi i = 0; i < row; i++)
		delete p[i];

	for (usi i = 0; i < row; i++)
		tmp[i][col] = 0;

	for (usi i = 0; i < row; i++)
		p[i] = tmp[i];
	
	++col;
}

template <typename T>
void MtxDAddRowN(T **& p, usi &row, const usi &col, const usi N){
	T ** tmp = new T *[row + 1];
	for (usi i = 0, j = 0; i < row + 1; i++){
		if (i == N){
			for (usi j = 0; j < col; j++)
				tmp[i] = new T[col];
		}
		else
			j++;
		tmp[i] = p[j];
	}
	delete[] p;
	p = tmp;
	++row;
}
template <typename T>
void MtxDAddColN(T **& p, usi &row, usi &col, const usi N);

template <typename T>
void MtxDCopyData(T **& source, T **& destination, const usi &row, const usi &col){
	for (usi i = 0; i < row; i++)
		for (usi j = 0; j < col; j++)
			destination[i][j] = source[i][j];
}