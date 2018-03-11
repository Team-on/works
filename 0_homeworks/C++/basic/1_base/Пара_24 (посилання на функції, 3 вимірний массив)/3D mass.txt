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
void AddRowInThirdDimention(T ***&p, usi mtxCnt, usi &sizerow, usi sizecol);

int main() {
	srand(time(0));

	usi mtxCnt = 3;
	usi sizerow = 4;
	usi sizecol = 8;
	int ** *p = new int **[mtxCnt];
	for (usi i = 0; i < mtxCnt; i++)
		p[i] = new int *[sizerow];
	for (usi i = 0; i < mtxCnt; i++)
		for (usi j = 0; j < sizerow; j++)
			p[i][j] = new int[sizecol];


	for (usi i = 0; i < mtxCnt; i++){
		for (usi j = 0; j < sizerow; j++){
			for (usi k = 0; k < sizecol; k++){
				*(*(*(p + i) + j) + k) = rand() % 9 + 1;
				cout << p[i][j][k] << s;
			}
			cout << endl;
		}
		cout << endl;
	}

	AddRowInThirdDimention(p, mtxCnt, sizerow, sizecol);

	
	for (usi i = 0; i < mtxCnt; i++)
		for (usi j = 0; j < sizerow; j++)
			delete[] p[i][j];
	for (usi i = 0; i < mtxCnt; i++)
		delete[] p[i];
	delete[] p;


	return 0;
}

template <typename T>
void AddRowInThirdDimention(T ***&p, usi mtxCnt, usi &sizerow, usi sizecol){
	int ** *pTmp = new int **[mtxCnt];
	for (usi i = 0; i < mtxCnt; i++)
		pTmp[i] = new int *[sizerow + 1];
	for (usi i = 0; i < mtxCnt; i++)
	for (usi j = 0; j < sizerow + 1; j++)
		pTmp[i][j] = new int[sizecol];

	for (usi i = 0; i < mtxCnt; i++)
		for (usi j = 0; j < sizerow; j++)
			for (usi k = 0; k < sizecol; k++)
				pTmp[i][j][k] = *(*(*(p + i) + j) + k);

	for (usi i = 0; i < mtxCnt; i++)
		for (usi j = 0; j < sizerow; j++)
			pTmp[i][j][sizerow] = 0;

	for (usi i = 0; i < mtxCnt; i++)
		for (usi j = 0; j < sizerow; j++)
			delete[] p[i][j];
	for (usi i = 0; i < mtxCnt; i++)
		delete[] p[i];
	delete[] p;

	int ** *p = new int **[mtxCnt];
	for (usi i = 0; i < mtxCnt; i++)
		p[i] = new int *[sizerow + 1];
	for (usi i = 0; i < mtxCnt; i++)
	for (usi j = 0; j < sizerow + 1; j++)
		p[i][j] = new int[sizecol];

	for (usi i = 0; i < mtxCnt; i++)
	for (usi j = 0; j < sizerow + 1; j++)
	for (usi k = 0; k < sizecol; k++)
		*(*(*(p + i) + j) + k) = pTmp[i][j][k];

	++sizerow;
}