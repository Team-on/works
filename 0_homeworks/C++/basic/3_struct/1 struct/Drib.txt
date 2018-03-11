#include <iostream>
#include <cmath>

using namespace std;
const char s = ' ';
const char tab = '\t';
#define usi unsigned short int


struct drib{
	int up, down;
	drib(){
		up = 0;
		down = 0;
	}
	drib(int up, int down){
		this->up = up;
		this->down = down;
	}

	void Print(){
		int chile = up / down;
		if (chile != 0){
			if (up % down == 0){
				cout << chile << endl;
			}
			else{
				cout << s << up % down << endl;
				cout << chile << "--" << endl;
				cout << s << down << endl;
			}
		}
		else{
			cout << up << endl;
			cout << "--" << endl;
			cout << endl << down << endl;
		}
		cout << endl;
	}

};

drib DribMultiple(drib a, drib b){
	drib tmp;
	tmp.up = a.up * b.up;
	tmp.down = a.down * b.down;
	return tmp;
}

drib DribDiv(drib a, drib b){
	drib tmp;
	tmp.up = a.up * b.down;
	tmp.down = a.down * b.up;
	return tmp;
}

drib DribAdd(drib a, drib b){
	drib tmp;
	tmp.up = (a.up * b.down) + (b.up * a.down);
	tmp.down = a.down * b.up;
	return tmp;
}

drib DribMin(drib a, drib b){
	drib tmp;
	tmp.up = (a.up * b.down) - (b.up * a.down);
	tmp.down = a.down * b.up;
	return tmp;
}

drib DribScor(drib tmp){
	int dil = (tmp.up < tmp.down) ? tmp.down : tmp.up;
	while (2 <= dil--){
		if (tmp.up % dil == 0 && tmp.down % dil == 0){
			tmp.up /= dil;
			tmp.down /= dil;
		}
	}

	return tmp;
}

void main(){

	drib a(2, 5), b(1, 6), c(0, 0);

	drib (*p[]) (drib, drib) = { DribMultiple, DribDiv, DribAdd, DribMin };

	for (usi i = 0; i < sizeof(p) / sizeof(p[0]); i++){
		c = p[i](a, b);
		c.Print();

		c = DribScor(c);
		c.Print();

		cout << endl;
	}

}