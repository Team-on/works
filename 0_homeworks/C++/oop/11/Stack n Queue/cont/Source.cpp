#include <iostream>
using namespace std;

#include "StackArr.h"
#include "Queue.h"

int main() {
	/*
	StackArr <char> st;

	char arr[256] = { 0 };
	cin.getline(arr, 255);

	for (int i = 0; i < strlen(arr); ++i) {
		if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{' )
			st.push(arr[i]);
		else if (arr[i] == ')' || arr[i] == ']' || arr[i] == '}') {
			char curr = st.pop();
			if (!(curr == arr[i] - 2 || curr == arr[i] - 1)) {
				st.push(0);
				break;
			}
		}
	}
	if (st.isEmpty())
		cout << '+';
	else
		cout << '-';
	cout << endl;	
	*/

	///*
	Queue <char> qu;
	char arr[500] = { 0 };
	//cin.getline(arr, 255);
	int i;
	for (i = 0; i < 256; ++i)
		arr[i] = 'a';
	
	const char *p = arr;
	while (*p)
		qu.push(*(p++));
	cout << endl;
	cout << endl;

	while (--i >= 50)
		cout << qu.pop();
	cout << endl;
	cout << endl;
	qu.push('b'); qu.push('b'); qu.push('b');

	while (!qu.isEmpty())
		cout << qu.pop();
	//*/

	cout << endl;
	system("pause");
	return 0;
}