#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//---------------------------------------------------------------------------------------------------------------
int Sum(int min, int max);					//Сума елементів з min по max
int Multiple();								//Множення а на b
int absolute();								//Модуль a
int power(int a, int b);					//а в степені b
int factorial();							//а!
int factorial_help(int a);					//а! help. Даби не писати додатково cin.
void Q();									//Розвязую квадратне рівняння
double S_col();								//Площа кола
double L_col();								//Довжина круга
double S_triangle();						//Площа трикутика
long number_cnt();							//Кількість цифр в числі


//---------------------------------------------------------------------------------------------------------------
const char znak_pisla_coma = 6;
const char array_size = 10;
const double pi = 103993./33102;

//---------------------------------------------------------------------------------------------------------------
void main(){





}

int Sum(int min, int max){
	int a, b;

	cin >> a >> b;

	int sum = 0;
	for (int i = min; i < max; i++)
		sum += i;
	cout << sum << endl;
	return sum;
}

int Multiple(){
	int a, b;

	cin >> a >> b;

	int sum = 0;
	for (int i = 0; i < b; i++)
		sum += a;
	return sum;
}

int absolute(){
	int a;
	cin >> a;
	return (a < 0) ? -a: a;
}

int power(int a, int b){
	int powr = 1;

	for (int i = 0; i < b; i++)
		powr *= a;

	return powr;
}

int factorial(){
	int a;
	cin >> a;
	return  factorial_help(a);
}

int factorial_help(int a){
	return  (a == 1) ? 1 : a * factorial_help(a - 1);
}

void Q(){		
	double a, b, c, d, x1, x2, obmen;
	cin >> a >> b >> c;

	d = power(b,2) - 4 * a * c;

	if (a == 0 && b == 0 && c == 0)
		cout << 3;
	else if (a == 0 && b == 0 && c != 0)
		cout << 0;
	else if (a == 0 && b != 0){
		x1 = -c / b;
		cout << 1 << " " << x1 << endl;
	}
	else if (d > 0){
		x1 = (-b + sqrt(d)) / (2 * a);
		x2 = (-b - sqrt(d)) / (2 * a);

		if (x1 > x2){
			obmen = x1;
			x1 = x2;
			x2 = obmen;
		}

		cout << 2 << " " << x1 << " " << x2 << endl;
	}
	else if (d == 0){
		x1 = -b / (2 * a);

		cout << 1 << " " << x1 << endl;
	}
	else
		cout << 0 << endl;

}

double S_col(){
	double R;
	cin >> R;
	R = pi * power(R, 2);
	return R;
}

double L_col(){
	double R;
	cin >> R;
	R = 2 * pi * R;
	return R;
}

double S_triangle(){
	double S, a, b, c, p;
	cin >> a >> b >> c;

	if (a < b + c && b < a + c && c < b + a){
		p = (a + b + c) / 2;

		S = sqrt(p * (p - a) * (p - b) * (p - c));

		return S;
	}
	else
		return 0;
}

long number_cnt(){
	int n, i = 0;

	cin >> n;

	while (n > 0){
		i++;
		n = n / 10;
	}

	return i;
}