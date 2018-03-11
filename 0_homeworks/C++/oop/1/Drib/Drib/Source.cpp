#include <iostream>

using namespace std;



class Drib{
private:
	int  up, down;

	void Scor(){
		int dil = (up < down) ? down : up;
		while (2 <= dil--){
			if (up % dil == 0 && down % dil == 0){
				up /= dil;
				down /= dil;
			}
		}
		if (up == down){
			up = down = 1;
		}
	}
public:
	Drib(){
		up = 0;
		down = 1;
	}

	void SetUp(int newUp){
		up = newUp;
	}
	void SetDown(int newDown){
		if (newDown != 0)
			down = newDown;
	}

	void Print(){
		Scor();
		if (down == 1)
			cout << up;
		else if (up == 0)
			cout << 0;
		else
			cout << up << "/" << down;
	}

	float GetDrib(){
		return float(up) / down;
	}

	void Add(Drib second){
		up = up * second.down + second.up * down;
		down *= second.down;
	}
	void Min(Drib second){
		up = up * second.down - second.up * down;
		down *= second.down;
	}
	void Mult(Drib second){
		up *= second.up;
		down *= second.down;
	}
	void Dil(Drib second){
		down *= second.up;
		up *= second.down;
	}
};

void hello() {
	cout << "Hello!" << endl;
}

#pragma startup hello 100

void main(){
//	hello();
	Drib a, b;

	int up, down;
	cout << "a.Up: ";		
	cin >> up;
	cout << "a.Down: ";	
	do{
		cin >> down;
		if (down == 0)
			cout << "ERROR" << endl;
	} while (down == 0);
	a.SetUp(up); a.SetDown(down);
	cout << "b.Up: ";		
	cin >> up;
	cout << "b.Down: ";	
	do{
		cin >> down;
		if (down == 0)
			cout << "ERROR" << endl;
	} while (down == 0);
	b.SetUp(up); b.SetDown(down);
	Drib c = a;

	//void(*pf)(Drib s) =  Drib.Min;

	c.Add(b);
	a.Print(); cout << " + "; b.Print(); cout << " = "; c.Print(); cout << endl;

	c = a;
	c.Min(b);
	a.Print(); cout << " - "; b.Print(); cout << " = "; c.Print(); cout << endl;

	c = a;
	c.Mult(b);
	a.Print(); cout << " * "; b.Print(); cout << " = "; c.Print(); cout << endl;

	c = a;
	c.Dil(b);
	a.Print(); cout << " / "; b.Print(); cout << " = "; c.Print(); cout << endl;

	system("pause");
}


