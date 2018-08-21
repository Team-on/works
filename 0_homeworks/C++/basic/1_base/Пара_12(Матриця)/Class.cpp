#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

void main(){
	setlocale(0, "RUS");
	srand(time(0));


	const char size_row = 5;
	const char size_col = 5;
	
	short arr[size_row][size_col];

	short sum_arr = 0, sum_row[size_row], sum_diag_1 = 0, sum_diag_2 = 0,a = 0;

	for (int i = 0; i < size_row; i++){
		a = 0;
		//sum_row[i] = 0;
		cout << "\t\t  ";
		for (int j = 0; j < size_col; j++){
			arr[i][j] = rand() % 10;
			cout << setw(3) << arr[i][j];
			a += arr[i][j];
			/*sum_arr += arr[i][j];
			sum_row[i] += arr[i][j];

			if (i == j)
				sum_diag_1 += arr[i][j];
			if (i + j == size_col - 1)
				sum_diag_2 += arr[i][j];*/
		}
		cout << "  Sum: " << a << endl;
	}
	
	//for (int i = 0; i < size_row; i++)
	//	cout << "Row [" << i+1 << "] sum is: " << sum_row[i] << "\t\t" << "  Average: " << sum_row[i] * 1. / size_row << endl;

	//cout << endl << "Diagonal 1(\\) sum is: " << sum_diag_1 << "\t  Diagonal 2(/) sum is: " << sum_diag_2 << endl;
		 
	//cout << endl << "Array sum is: " << sum_arr << "\t\t  Array average: " << sum_arr * 1. / (size_row * size_col) << endl << endl;

	/*short max_el = arr[0][0], min_el = arr[0][0];

	for (int i = 0; i < size_row; i++){
		for (int j = 0; j < size_col; j++){
			if (max_el < arr[i][j])
				max_el = arr[i][j];
			else if (min_el > arr[i][j])
				min_el = arr[i][j];

		}
	}

	cout << "Max: " << max_el << "\nMin: " << min_el << endl;*/

	/*
	int a = 1;
	for (int i = 0; i < size_row; i++){
		for (int j = 0; j < size_col; j++){
			arr[i][j] = a++;
			cout << setw(4) << arr[i][j];
		}
		cout << endl;
	}
	*/

	//int obmen, obmen2;

	//

	//for (int i = 0; i < size_row; i++){
	//	obmen = arr[i][0];
	//	for (int j = 1; j < size_col; j++){
	//		if (j == size_col - 1){
	//			obmen2 = arr[i][j];
	//			arr[i][j] = obmen;
	//			arr[i][0] = obmen2;
	//		}
	//		else{
	//			obmen2 = arr[i][j];
	//			arr[i][j] = obmen;
	//			obmen = obmen2;
	//		}
	//	}
	//}
	//cout << endl; cout << endl;
	//for (int i = 0; i < size_row; i++){
	//	cout << "\t\t  ";
	//	for (int j = 0; j < size_col; j++){
	//		cout << setw(3) << arr[i][j];
	//	}
	//	cout << endl;
	//}

	//for (int i = 0; i < size_row; i++){
	//	obmen = arr[i][size_col -1];
	//	for (int j = size_col-1; j >=0; j--){
	//		if (j == 0){
	//			obmen2 = arr[i][j];
	//			arr[i][j] = obmen;
	//			arr[i][size_col-1] = obmen2;
	//		}
	//		else{
	//			obmen2 = arr[i][j];
	//			arr[i][j] = obmen;
	//			obmen = obmen2;
	//		}
	//	}
	//}
	//cout << endl; cout << endl;
	//for (int i = 0; i < size_row; i++){
	//	cout << "\t\t  ";
	//	for (int j = 0; j < size_col; j++){
	//		cout << setw(3) << arr[i][j];
	//	}
	//	cout << endl;
	//}

	//for (int i = 0; i < size_row; i++){
	//	for (int j = size_col-1; j > 0; j--){
	//		obmen = arr[i][0];
	//		arr[i][0] = arr[i][j];
	//		arr[i][j] = obmen;
	//	}
	//}


	//for (int i = 0; i < size_row; i++){
	//	cout << "\t\t  ";
	//	for (int j = 0; j < size_col; j++){
	//		cout << setw(3) << arr[i][j];
	//	}
	//	cout << endl;
	//}

	/*short sumarr = 0, sumarr1 = 0, arr_copy1[size_col];

	for (int i = 0; i < size_row; i++){
		sumarr = 0;
		for (int j = 0; j < size_col; j++){
			sumarr += arr[i][j];
		}
		
		if (sumarr1 < sumarr){
			sumarr1 = sumarr;
			for (int j = 0; j < size_col; j++)
				arr_copy1[j] = arr[i][j];

		}

	}

	cout << endl << endl;

	for (int i = 0; i < size_row; i++){
		cout << "\t\t  ";
		for (int j = 0; j < size_col; j++){
			arr[i][j] = arr_copy1[j];
			cout << setw(3) << arr[i][j];
		}
		cout << endl;
	}*/





}

