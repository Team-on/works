#include <iostream>
#include <ctime>

#define usi unsigned short int
using std::cin;
using std::cout;
const char endl = '\n';
const char tab = '\t';
const char s = ' ';

int MainMenu();

template <typename T>
void ArrCreate(T *&a, const int size);
template <typename T>
void ArrDelete(T *&a);
template <typename T>
void ArrFill(T *&a, usi size, T left = 1, T right = 10);
template <typename T>
void ArrPrint(T *&a, const int size);
template <typename T>
void TakeSize(T &size);

template <typename T1, typename T2>
void ArrCopy(T1 arrInput[], T2 arrResult[], usi size);
template <typename T>
void ArrAdd(T *&arr, T data, usi &size);

template <typename T>
void ArrRepeatEven(T *&a,usi &size);
template <typename T>
void ArrTripleOdd(T *&a, usi &size);

template <typename T>
void ArrDeleteByData(T *&a, usi &size, T data);
template <typename T>
void ArrModaFind(T *&a, usi size);
template <typename T>
void ArrModaDelete(T *&a, usi &size);

template <typename T>
void ArrDeleteByIndex(T *&a, usi &size, usi index);
template <typename T>
void ArrSortByDeleting(T *&a, usi &size);

template <typename T>
void ArrReverse(T *&a, usi size);
template <typename T>
void ArrReverseCopy(T *&a, usi size);

int main(){
	srand(time(0));
	setlocale(0, "RUS");

	int *a = NULL;
	usi size = 0, menu;

		TakeSize(size);
		ArrCreate(a, size);
		ArrFill(a, size, 0, 5);
		ArrPrint(a, size);

		ArrSortByDeleting(a, size);
		ArrPrint(a, size);

		ArrDelete(a);
	return 0;
}

int MainMenu(){
	int menu;
	cout << "[0] - Input size" << endl;
	cout << "[1] - Fill Array" << endl;
	cout << "[2] - Print Array" << endl;
	cout << "[3] - Repeat all even numbers in array" << endl;
	cout << "[4] - Triple all odd numbers in array" << endl;
	cout << "[5] - Create Array" << endl;
	cout << "[6] - Delete Array" << endl;
	cout << "[other] - exit" << endl << endl;
	cin >> menu;
	cout << endl;
	return menu;
}

template <typename T>
void ArrCreate(T *&a, const int size){
	if (a != NULL){
		cout << "ERROR in CreateArr! Array adress is not NULL" << endl;
		return;
	}
	if (size <= 0){
		cout << "ERROR in CreateArr! size <= 0" << endl;
		return;
	}
	a = new int[size];
}
template <typename T>
void ArrDelete(T *&a){
	if (a == NULL){
		cout << "ERROR in DeleteArr! Array adress is NULL" << endl;
		return;
	}
	delete [] a;
	a = NULL;
}
template <typename T>
void ArrFill(T *&a, usi size, T left, T right){
	if (a == NULL){
		cout << "ERROR in ArrFill! Array adress is NULL" << endl;
		return;
	}
	if (size <= 0){
		cout << "ERROR in ArrFill! size <= 0" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		*(a + i) = rand() % (left + right + 1) + left;
}
template <typename T>
void ArrPrint(T *&a, const int size){
	if (a == NULL){
		cout << "ERROR in ArrPrint! Array adress is NULL" << endl;
		return;
	}
	if (size <= 0){
		cout << "ERROR in ArrPrint! size <= 0" << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		cout << *(a + i) << s;
	cout << endl;
}
template <typename T>
void TakeSize(T &size){
	cin >> size;
}

template <typename T>
void ArrAdd(T *&arr, T data, usi &size){
	T *tmpArr = new T[size + 1];
	ArrCopy(arr, tmpArr, size);
	delete[] arr;
	arr = tmpArr;
	arr[size] = data;
	size++;
}
template <typename T1, typename T2>
void ArrCopy(T1 arrInput[], T2 arrResult[], usi size){
	for (int i = 0; i < size; i++)
		*(arrResult + i) = *(arrInput + i);
}

template <typename T>
void ArrRepeatEven(T *&a, usi &size){
	usi cnt = 0;
	T *tmp = new T[cnt];
	for (int i = 0; i < size; i++){
		ArrAdd(tmp, *(a + i), cnt);
		if (*(a + i) % 2 == 0 && *(a + i) != 0)
			ArrAdd(tmp, *(a + i), cnt);
	}
	delete[] a;
	a = tmp;
	size = cnt;
}
template <typename T>
void ArrTripleOdd(T *&a, usi &size){
	usi cnt = 0;
	T *tmp = new T[cnt];
	for (int i = 0; i < size; i++){
		ArrAdd(tmp, *(a + i), cnt);
		if (*(a + i) % 2 == 1 && *(a + i) != 0){
			ArrAdd(tmp, *(a + i), cnt);
			ArrAdd(tmp, *(a + i), cnt);
		}
	}
	delete[] a;
	a = tmp;
	size = cnt;
}

template <typename T>
void ArrDeleteByData(T *&arr, usi &size, T data){
	usi j = 0;
	T *tmpArr = new T[j];
	
	for (int i = 0; i < size; i++)
		if (*(arr + i) != data)
			ArrAdd(tmpArr, *(arr + i), j);

	delete[] arr;
	arr = tmpArr;
	size = j;
}
//template <typename T>
//void ArrModaFind(T *&arr, usi size){
//	usi newCnt = 0, maxCnt = 0;
//	T maxData;
//	for (int i = 0; i < size; i++){
//		for (int i = 0; i < size; i++){
//			if (*(arr + i) == *(arr + j) && i != j)
//				newCnt++;
//		}
//		if (newCnt > maxCnt){
//			maxCnt = newCnt;
//			maxData = *(arr + i);
//		}
//	}
//}
template <typename T>
void ArrModaDelete(T *&arr, usi &size){
	usi newCnt = 1, maxCnt = 1;
	T maxData = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (*(arr + i) == *(arr + j) && i != j)
				newCnt++;
		}
		if (newCnt > maxCnt){
			maxCnt = newCnt;
			maxData = *(arr + i);
		}
		newCnt = 0;
	}
	cout << "Moda is: " << maxData << "\nWith " << maxCnt << " repeats" << endl;
	ArrDeleteByData(arr, size, maxData);
}

template <typename T>
void ArrReverse(T *&arr, usi size){
	T arrReversed = new T[size];
	for (int i = 0; i < size; i++)
		*(arrReversed + i) = *(arr + size - i);
	delete[] arr;
	arr = arrReversed;
}
template <typename T>
void ArrReverseCopy(T *&arrInput, T *&arrResult, usi size){
	ArrCopy(arrInput, arrResult, size);
	ArrReverse(arrInput, size);
}

template <typename T>
void ArrDeleteByIndex(T *&arr, usi &size, usi index){
	usi j = 0;
	T *tmpArr = new T[j];

	for (int i = 0; i < size; i++)
		if (i != index)
			ArrAdd(tmpArr, *(arr + i), j);

	delete[] arr;
	arr = tmpArr;
	size = j;
}

template <typename T>
void ArrSortByDeleting(T *&arr, usi &size){
	T *LongestEscape = NULL;
	usi LongestSize = 0;
	for (usi j = 0; j < size; j++){
		T *tmpArr = new T[size], tmpSize = size;;
		ArrCopy(arr, tmpArr, tmpSize);

		for (usi i = 0; i < tmpSize - 1; i++){
			if (*(tmpArr + i) > *(tmpArr + i + 1)){
				ArrDeleteByIndex(tmpArr, tmpSize, i + 1);
				i--;
			}
		}
		if (tmpSize > LongestSize)
			ArrCopy(tmpArr, LongestEscape, tmpSize);
	}
}

