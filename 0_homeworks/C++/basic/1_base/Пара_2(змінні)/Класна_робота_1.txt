#include <iostream>
using namespace std;

void main(){
setlocale(0,"rus");

/* --------------------------------Принцип годинника-----------------------------------------
short var=100000;
cout <<"You var is "<<var<<endl;
 var=-100000;
cout <<"You var is "<<var<<endl;
 var=32777;
cout <<"You var is "<<var<<endl;
 var=-32777;
cout <<"You var is "<<var<<endl;
*/

/*  --------------------------------Ввід-----------------------------------------
short var;
cin>>var;
cout <<"You var is "<<var<<endl;
*/

/*  --------------------------------Сумування-----------------------------------------
short a,b,c;
cin>>a>>b>>c;
cout <<"You sum is "<<a+b+c<<endl;

short a,b,c,sum;				// Збереження в іншу змінну
cin>>a>>b>>c;
sum=a+b+c;
cout <<"You sum is "<<sum<<endl;

short a,sum=0;					// Та сама штука двома змінними
cin>>a; sum=sum+a;				// sum=sum+a це те саме що й sum+=a
cin>>a; sum+=a;
cin>>a; sum+=a;
cout <<"You sum is "<<sum<<endl;
*/

/* --------------------------------Дійсьні числа і їх змінні-----------------------------------------
int a =2.66;
double b=222.5555;					// так і не вїхав в різницю між double і float
float  c=222.5555;
cout <<"You int is "<<a<<endl;
cout <<"You double is "<<b<<endl;
cout <<"You float is "<<c<<endl;
*/

/* --------------------------------Кратність-----------------------------------------
	int a;
	cin>>a;
	cout<<"You number is multiple to 2, if 1 - unmultiple"<<endl<<a%2<<endl;
	cin>>a;
	cout<<"You number is multiple to 3, if 1 or 2 - unmultiple"<<endl<<a%3;
*/

/* --------------------------------Константи-----------------------------------------
const double p=3.14;
short R;
cout<<"R="; cin>>R;
cout<<"S="<<p*R*R<<endl;
cout<<"L="<<p*R*2<<endl<<endl;
{
cout<<"With more numbers after comma"<<endl;	// Перевірка локальності констант. Правда - вони є локальними
const double p=3.1415;							// Одні і ті ж імена в різних дужках, якщо змінна переоголошена,
cout<<"S="<<p*R*R<<endl;						//  але не перепризначена.
cout<<"L="<<p*R*2<<endl;
}
*/

/* --------------------------------Зміна типів на одну дію-----------------------------------------
short a=2,b=4;
cout<<double(a)/b<<endl;
*/

short a,b,c;
cin>>a>>b>>c;
cout<<"average="<<float(a+b+c)/3<<endl;

cout<<"Хитрий метод:"<<endl;				//Після того як 3 стала 3. , то це став Double.
cout<<"average="<<(a+b+c)/3.<<endl;
}