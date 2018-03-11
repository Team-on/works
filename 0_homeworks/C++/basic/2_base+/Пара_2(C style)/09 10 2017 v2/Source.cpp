#include <iostream>

using namespace std;
typedef unsigned short int usi;
#define pause system("pause")
#define clear system("cls")

#define DEBUG

int main() {
	setlocale(0, "rus");

	usi sizeRow = 3;
	usi sizeCol = 3;

#ifdef DEBUG
	scanf("%d %d", &sizeRow, &sizeCol);
#endif // DEBUG



	int **mtx = (int**) calloc(sizeRow, sizeof(int*));
	
	for(usi i = 0; i < sizeRow; i++)
		mtx[i] = (int*)calloc(sizeCol, sizeof(int*));

	for (usi i = 0; i < sizeRow; i++)
		for (usi j = 0; j < sizeCol; j++)
			mtx[i][j] = rand() % 9 + 1;

	for (usi i = 0; i < sizeRow; i++) {
		for (usi j = 0; j < sizeCol; j++)
			printf("%d ", mtx[i][j]);
		printf("\n");
	}
	printf("\n");


	for (usi i = 0; i < sizeRow; i++)
		free(mtx[i]);
	free(mtx);
	pause;
	return 0;
}

