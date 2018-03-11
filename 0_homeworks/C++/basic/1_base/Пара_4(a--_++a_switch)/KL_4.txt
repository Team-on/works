#include <iostream>;
using namespace std;

void main(){
/**********************************************************сумування цифр числа********************************************************
int a,b,c;
cin>>a;

if(a>=100&&a<1000){
	a=a/100+(a/10)%10+a%10;
	cout<<a<<endl;;
}	
else
	cout<<"ERROR\a"<<endl;
*/
	/**********************************************************мульти if********************************************************
unsigned short a;
for(;;){
cin>>a;
if (0>a||23<a)
	cout << "ERROR\a" << endl;
else if (a<=5)
	cout << "Goog night!" << endl;
else if (a<=10)
	cout << "Goog morning!" << endl;
else if (a<=15)
	cout << "Goog day!" << endl;
else if (a<=20)
	cout << "Goog evening!" << endl;
else
	cout << "Goog night!" << endl;
}
*/

/* *********************************************************switch,case********************************************************
unsigned short a;

cin>>a;
switch(a){
case 1:
	cout << "very bad" << endl;
	break;
case 2:
	cout << "bad" << endl;
	break;
case 3:
	cout << "normal" << endl;
	break;
case 4:
	cout << "good" << endl;
	break;
case 5:
	cout << "very good" << endl;
	break;
default:
	cout << "Input number from 1 to 5" << endl;
}
*/

/* *********************************************************Меню********************************************************
	unsigned short a;
	double grn,kyrs;
	cout<<"Enter the amount of UAH"<<endl;
	cin>>grn;
	cout << "input [1] to convert UAH to EUR" << endl;
	cout << "input [2] to convert UAH to USD" << endl;
	cout << "input [3] to convert UAH to RUB" << endl;
	cin >> a;

	switch (a){
	case 1:
		cout<<"Input EUR rate"<<endl; cin>>kyrs;
		cout <<grn<< " UAH is " <<grn/kyrs<<" EUR"<< endl;
		break;
	case 2:
		cout<<"Input USD rate"<<endl; cin>>kyrs;
		cout <<grn<< " UAH is " <<grn/kyrs<<" USD"<< endl;
		break;
	case 3:
		cout<<"Input RUB rate"<<endl; cin>>kyrs;
		cout <<grn<< " UAH is " <<grn/kyrs<<" RUB"<< endl;
		break;
	default:
		cout << "Input number from 1 to 3" << endl;

}
*/

	/* *********************************************************калькулятор 1.1********************************************************
	double a, c;
	char b;
	cout << "\nVvedit vuraz" << endl;
	cin >> a >> b >> c;
	cout<<a<<b<<c<<"=";
switch(b){
case '+':
	cout<<a+c;
	break;
case '-':
	cout << a - c;
	break;
case '*':
	cout << a * c;
	break;
case '/':
	if (c==0)
		cout << "Div by zero";
	else
		cout<<a/c;
	break;
default:
	cout << "ERROR";
}
*/
int month;
cout << "Input months number" << endl;
cin >> month;
switch (month){
case 1:case 2:case 12:
	cout << "Winter"<<endl;
	break;
case 6:case 7:case 8:
	cout << "Autumn" << endl;
	break;
case 3:case 4:case 5:
	cout << "Spring" << endl;
	break;
default:
	if (month<12 && month>0)
		cout << "Summer" << endl;
	else
		cout << "Input number from 1 to 12" << endl;
}

}