#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std; 

int main() {
	int size;
	scanf("%d", &size);
	stack<int> max;
	string s, sub;
	int value;
	cin.ignore();
	while (size--) {
		getline(cin, s);
		if (s.length() == 3) {
			sub = s.substr(0, 3);
			if (sub == "pop" && !max.empty())
				max.pop();
			else if (sub == "max" && !max.empty())
				printf("%d\n", max.top());
		}
		else {
			value = atoi(s.substr(5).c_str());
			if (!max.empty()) {
				if (value > max.top())
					max.push(value);
				else
					max.push(max.top());
			}
			else
				max.push(value);
		}
	}

	printf("\n");
	system("pause");
	return 0;
}