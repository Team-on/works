#include <iostream>

using namespace std;

union UNI {
	int i;
	bool b[4];
};


int main() {
	UNI u;

	while (1) {
		cin >> u.i;

		for (int i = 0; i < 4; i++)
			cout << u.b[i] << endl;
		cout << endl;
	}

	return 0;
}