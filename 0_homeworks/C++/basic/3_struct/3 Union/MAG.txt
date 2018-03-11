#include <iostream>

using namespace std;

template <typename T>
void arrPushBack(T *&arr, int &size) {
	T *tmp = new T[size + 1];
	for (int i = 0; i < size; i++)
		tmp[i] = arr[i];
	delete[] arr;
	arr = tmp;
	size++;
}

struct TV {
	int diag;
	int pr;
	int wgh;
	
	void print() {
		cout << "Type: TV" << endl;
		cout << "Diag: " << diag << endl;
		cout << "Price: " << pr << endl;
		cout << "Weight: " << wgh << endl;
	}
	void get() {
		cout << "Diag: ";
		cin >> diag;
		cout << "Price: ";
		cin >> pr;
		cout << "Weight: ";
		cin >> wgh;
	}
};

struct PC {
	double ff;
	int ram;
	int vram;

	void print() {
		cout << "Type: PC" << endl;
		cout << "FF: " << ff << endl;
		cout << "RAM: " << ram << endl;
		cout << "VRAM: " << vram << endl;
	}
	void get() {
		cout << "FF: ";
		cin >> ff;
		cout << "RAM: ";
		cin >> ram;
		cout << "VRAM: ";
		cin >> vram;
	}
};

struct MTEL {
	double diag;
	short version;
	short sim;

	void print() {
		cout << "Type: MTEL" << endl;
		cout << "diag: " << diag << endl;
		cout << "version: " << version << endl;
		cout << "sim: " << sim << endl;
	}
	void get() {
		cout << "diag: ";
		cin >> diag;
		cout << "version: ";
		cin >> version;
		cout << "sim: ";
		cin >> sim;
	}
};

union TVPC {
	TV tv;
	PC pc;
	MTEL mtel;
};

struct Pricelist{
	TVPC dt;
	char t;

	void print() {
		if (t == 'P')
			dt.pc.print();
		else if (t == 'T')
			dt.tv.print();
		else if (t == 'M')
			dt.mtel.print();
		cout << endl;
	}

	void get(char t) {
		this->t = t;
		if (t == 'P')
			dt.pc.get();
		else if (t == 'T')
			dt.tv.get();
		else if (t == 'M')
			dt.mtel.get();
	}
};

int main() {
	int size = 0;
	Pricelist *arr = new Pricelist[size];

	while(1){
		char t = 1;
		cout << "Type: ";
		cin >> t;

		if (t == '0')
			break;

		arrPushBack(arr, size);
		arr[size - 1].get(t);
		cout << endl; 
	}
	cout << endl;

	for (int i = 0; i < size; i++) 
		arr[i].print();
	

	return 0;
}


