#include <iostream>
#include "ArrayTemplate.h"

using namespace std;

void main() {
	ArrayTemplate <int> arr;
	cout << "IsEmpty\t\t" << arr.IsEmpty() << endl;
	cout << "GetSize\t\t" << arr.GetSize() << endl;
	cout << "GetUpperBound\t" << arr.GetUpperBound() << endl;
	cout << "GetData\t\t" << arr.GetData() << endl << endl;
	
	arr.SetSize(10);
	cout << "SetSize(10)\nIsEmpty\t\t" << arr.IsEmpty() << endl;
	cout << "GetSize\t\t" << arr.GetSize() << endl;
	cout << "GetUpperBound\t" << arr.GetUpperBound() << endl;
	cout << "GetData\t\t" << arr.GetData() << endl << endl;

	arr.Add(1); arr.Add(2); arr.Add(3);  arr.FreeExtra();
	cout << "Add([1, 2, 3])  FreeExtra\n";
	cout << arr << endl;
	cout << "GetSize\t\t" << arr.GetSize() << endl;
	cout << "GetUpperBound\t" << arr.GetUpperBound() << endl << endl;

	cout << "GetAr(0)  SetAt(2, 1251)  arr.GetAt(2)\n";
	cout << arr << endl;
	cout << "arr[0]" << arr.GetAt(0) << '\n';
	arr.SetAt(2, 1251);
	cout << "arr[2]" << arr.GetAt(2) << endl << endl;


	cout << "[] test\n";
	for (int i = 0; i < arr.GetSize(); ++i)
		arr[i] = i - 10;
	cout << arr << endl << endl;
	
	cout << "Add if size <\nBEFORE\n";
	cout << "GetSize\t\t" << arr.GetSize() << endl;
	cout << "GetUpperBound\t" << arr.GetUpperBound() << endl;
	cout << arr << endl << endl;
	arr.Add(3);
	arr.Add(3);
	arr.Add(3);
	cout << "AFTER\nGetSize\t\t" << arr.GetSize() << endl;
	cout << "GetUpperBound\t" << arr.GetUpperBound() << endl;
	cout << arr << endl << endl;
	
	cout << "Append, arr = arr.Append(arr) \n";
	arr = arr.Append(arr);
	cout << arr << endl << endl;

	cout << "InsertAt(888888, 5), RemoveAt(i)  \n";
	arr.InsertAt(888888, 5);
	cout << arr << endl << endl;

	for (int i = arr.GetUpperBound(); i >= 0; i--) {
		if (arr[i] == 3) 
			arr.RemoveAt(i);
	}
	cout << arr << endl << endl;
	
	arr.RemoveAll();
	cout << "RemoveAll\n";
	cout << "IsEmpty\t\t" << arr.IsEmpty() << endl;
	cout << "GetSize\t\t" << arr.GetSize() << endl;
	cout << "GetUpperBound\t" << arr.GetUpperBound() << endl;
	cout << "GetData\t\t" << arr.GetData() << endl << endl;
	system("pause");
}