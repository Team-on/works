#include <iostream>

using namespace std;

template <typename T>
void Abs(T &a);
template <typename T>
void Swap(T *a, T *b);
template <typename T>
void Change(T *a, T *b);

void EXIT(){
	cout << "In exit" << endl;
	system("PAUSE");
}

template <typename T>
void Q(T a, T b, T c, T &x1, T &x2){
	double d = b * b - 4 * a * c;

	x1 = x2 = 0;

	if (d < 0)
		return;

	if (d == 0){
		x1 = x2 = -b / (2 * a);
	}
	else{
		x1 = (-b + sqrt(d)) / (2 * a);
		x2 = (-b - sqrt(d)) / (2 * a);
	}

}

int main(){
	atexit(EXIT);

	const char TAB = '\t';
	double a, b, c, x1, x2;
	
	cin >> a >> b >> c;

	Q(a, b, c, x1, x2);

	cout << x1 << TAB << x2 << endl;

	return 0;
}

template <typename T>
void Abs(T &a){
	if (a < 0)
		a *= -1;
}

template <typename T>
void Swap(T *a, T *b){
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

template <typename T>
void Change(T *a, T *b){
	if (*a == *b)
		return;
	if (*a > *b){
		*b *= 10;
		*a /= 10;
		return;
	}
	*a *= 10;
	*b /= 10;
}