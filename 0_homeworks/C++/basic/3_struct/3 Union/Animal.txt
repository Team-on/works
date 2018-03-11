#include <iostream>

using namespace std;

enum type { human, bird, hudoba, TYPECNT };

union Stat {
	int IQ;
	bool par;
	double spdFly;
};

struct Animal {
	double spd;
	type t;
	Stat s;
	
};

int main() {
	const int size = 3;
	Animal hr[size];

	for (int i = 0; i < size; i++){
		int ch;
		cout << "Type: ";
		cin >> ch;
		switch (ch) {
		case human:
			cout << "IQ: ";
			cin >> hr[i].s.IQ;
		break;
		case bird:
			cout << "spdFly: ";
			cin >> hr[i].s.spdFly;
		break;
		case hudoba:
			cout << "Par: ";
			cin >> hr[i].s.par;
		break;
		}
		hr[i].t = (type)ch;
		cout << "Gnd Spd: ";
		cin >> hr[i].spd;
		cout << endl;
	}

	for (int i = 0; i < size; i++) {
		cout << "Type: ";
		switch(hr[i].t) {
		case human:
			cout << "human" << endl;
			cout << "IQ: ";
			cout << hr[i].s.IQ;
		break;
		case bird:
			cout << "bird" << endl;
			cout << "Fly Spd: ";
			cout << hr[i].s.spdFly;
		break;
		case hudoba:
			cout << "hudoba" << endl;
			cout << "par: ";
			cout << hr[i].s.par;
		break;
		default:
			cout << hr[i].t;
			cout << endl;
		}
		if(hr[i].t < TYPECNT)
			cout << endl;

		cout << "Gnd Spd: ";
		cout << hr[i].spd;
		cout << endl;

		cout << endl;
	}

	return 0;
}


