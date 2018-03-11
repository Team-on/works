#include <iostream>
using namespace std;
void main()
{
	setlocale(0, "UTF8");
/* ----------------------------------------Трипл перевірка---------------------------------------------
	int a;
	cin >> a;

	if (a > 0)
		cout << a << ">0";
	else 
		if (a < 0)
			cout << a << "<0";
		else 
			cout << a << "=0";
*/
/* ----------------------------------------Операторп I---------------------------------------------
	int a;
	cin >> a;
	if (a >= 0 || a <= 6)
		cout << a << " ? [0;6]";
*/

	/* ----------------------------------------Чи влізе кірпіч в стіну---------------------------------------------
	int a,b,c;
	cout <<"Rozmir\n";
	cin >> a >> b;
	if (0 <= a && 0 <= b){
		if (a < b&&a!=b){
			a =a+ b;
			b = a - b;
			a =a- b;
		}
		if (a <= 6&&b<=3){
			cout << "+";
		}
		else cout<< "-";
	}
	else
		cout << "error";
	*/

	/* ----------------------------------------Калькулятор---------------------------------------------
	double a, c;
	char b;
	cout <<"Vvedit vuraz"<<endl;
	cin >>a>>b>>c;
	if (0 != c){
		cout << a << b << c << "=";
		if ('+' == b)
			a += c;
		else if ('-' == b)
			a -= c;
		else if ('*' == b)
			a *= c;
		else if ('/' == b)
			a /= c;
		cout << a << endl;
	}
	else
		cout << "Error";
	*/


	/* ----------------------------------------Кратності---------------------------------------------
	int a;
	cout << "Vvedit zminny" << endl;
	cin >>a;
	if (0 != a){
		if (0 == a % 2)
			cout << "Parne i ";
		else
			cout << "NEparne i ";
		if (double(a) / 3 == a / 3)
			cout << "kratne 3" << endl;
		else
			cout << "NEkratne 3" << endl;
	}
	else cout << "a= 0" << endl;
	*/

	int a,b;
	cout << "Vvedit zminni" << endl;
	cin >> a>>b;
	a= a<b?a:b;
	cout << "min " << a << endl;
}
