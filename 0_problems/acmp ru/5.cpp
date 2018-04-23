#include <iostream>
using namespace std;

int i;
int n;
int tmp;
int cnt, evenLen = -1;
int *even;

int main() {
	cin >> n;
	even = new int[n];
	for (i = 0; i < n; ++i) {
		cin >> tmp;
		if (tmp % 2 != 0) {
			cout << tmp << ' ';
			++cnt;
		}
		else
			even[++evenLen] = tmp;
	}

	cout << '\n';

	for (i = 0; i <= evenLen; ++i)
		cout << even[i] << ' ';

	cout << '\n';

	if (++evenLen >= cnt)
		cout << "YES";
	else
		cout << "NO";

	//system("pause");
	return 0;
}