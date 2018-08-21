#include <iostream>
#include <iomanip>
#include <windows.h>
#include <ctime>

using namespace std;

void main()
{
	srand(time(0));
	/*		Multiple table
		for (int i = 1; i <= 10; i+=2){
		for (int j = 1; j <= 10; j++){
		cout << i << " * " << j << " = " << i*j;
		cout <<"\t\t"<< i+1 << " * " << j << " = " << i*j << endl;
		}
		cout << endl;
		}
		*/

	/*		Pythagoras table
		int max;
		cout << "\t\t\tthe Pythagoras table" << endl;
		cout << "Input max number" << endl;
		cin >> max;

		for (int i = 1; i <= max; i++){
		for (int j = 1; j <= max; j++){
		cout << setw(3)<< j*i;
		}
		cout << endl;
		}
		*/

	/*		Sum table
	int max, number, numbersum, min;
	cout << "\t\t\tthe Sum table" << endl;
	cout << "Input min number" << endl;
	cin >> min;
	cout << "Input max number" << endl;
	cin >> max;

	for (int i = min; i <= max; i++){
	number = i;
	numbersum = 0;
	while (number>0){
	numbersum = numbersum + number % 10;
	number = number / 10;
	}
	if (numbersum >= 10){ cout << i << " with sum " << numbersum << endl; }
	}

	*/
	/*
		int N,anotherN=0;
		cout << "\t\t\tthe Re: Number" << endl;
		cout << "Input number" << endl;
		cin >> N;
		cout << "Normal:\t"<<N << endl;

		while (N>0){
		anotherN = anotherN*10 +  N % 10;
		N = N / 10;
		}
		cout << "Re: \t" << anotherN<<endl;
		*/

	/*	Sleep();
		cout << "Loading" << endl;

		for (int i = 1; i <= 10; i++){
		Sleep(500);
		cout << "*";
		}
		cout << endl;
		*/

	/* Array
	const short size_arr = 365;
	int arr[size_arr];

	for (int i = 0; i < size_arr; i++)
		arr[i] = rand()%25+1;

		cout <<"Day 1 is "<< arr[0] << "\n";
	for (int i = 1; i < size_arr; i++){
		cout <<"Day "<<i+1<<" is "<< arr[i]<<"\n";
		arr[0] += arr[i];
	}
	cout << "\nSum: \t" << arr[0]<<endl;
	cout << "Average: \t" << arr[0]*1. / size_arr<<endl;
	*/

	const short size_arr = 20;
	short j=1;
	int arr[size_arr];


	for (int i = 0; i < size_arr; i++){
			arr[i] = j;
			j += 2;
			cout << arr[i] << endl;
	}


}
