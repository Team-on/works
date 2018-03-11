#include "Header.h"

template <typename T>
void zero(T a, int size);

int main(){
	//Підготовка
	SET();
	const int size = 10;
	SET_ARR(size, 3, 1, 10);
	int a[size], sum_min_max, l, r;

	Arr_fill(a);
	Arr_printl(a);

	//Завдання 1
	sum_min_max = Arr_min(a) + Arr_max(a);
	cout << "Sum min and max is: " << sum_min_max << endl << endl;

	//Завдання 2
	zero(a,size);
	Arr_printl(a);

	//Завдання 3
	Arr_fill(a);
	Arr_printl(a);

	cout << "Left: ";
	cin >> l;
	cout << "Right: ";
	cin >> r;

	if (l >= 0 && r <= 20 && r >= l && r > 0){
		Arr_sort_vubor_fromto(a, size, l, r);
		Arr_printl(a);
	}
	else
		cout << "ERROR" << endl;

	return 0;
}


template <typename T>
void zero(T a, int size){
	int doubled = 1, pos;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (a[i] == a[j] && i != j){
				doubled++;
				pos = j;
			}
		}
		if (doubled == 2){
			a[i] = 0;
			a[pos] = 0;
			cout << "Changed element " << i << " and " << pos << endl;
		}
		doubled = 1;
	}

}


