#include <iostream>
using namespace std;

void main(){
/*
		short a = 1;
	while (a<=100){
		if (0 == a % 2) cout << a << endl; 
		a++;
	}
*/

/*
	short a = 1;
	while (a<=100){
		if (0 != a % 2) cout <<a<<"^2="<< a*a << endl; 
		a++;
		}
*/

/*
short a = 2, sum=0;
	while (a <= 50){
		if (0 == a % 2) sum+=a;
		a++;
	
	}
cout<<"Sum from 0 to 50 is "<<sum<<endl;
*/

/*
unsigned long long sum=1,chislo;
cin>>chislo;
cout<<chislo<<"!=";
	while (1 <= chislo){
		sum*=chislo;
	chislo--;
	}
cout<<sum<<endl;
*/

/*
int chislo;
short i=1;
cout<<"\t\t\t\tMultiple table"<<endl;
cout<<"Enter number"<<endl;
cin>>chislo;
	while (i <= 10){
		cout<<chislo<<"*"<<i<<"="<<i*i<<endl;
		i++;
	}
*/

/*
int sum=0,chislo;
short i;
cout<<"\t\t\t\tAverage and sum"<<endl;
cout<<"Enter the number of numbers"<<endl;
cin>>i;
int n=i;
	while (i > 0){
		cin>>chislo;
		sum+=chislo;
		i--;
	}
if(n!=0){
cout<<"Sum: "<<sum<<endl;
cout<<"Average: "<<sum*1./n<<endl;
}
else cout<<"ERROR\a"<<endl;
*/

/*
int tempMoreThan10=0,temp;
short i=1;
cout<<"\t\t\t\tThermometer"<<endl;
cout<<"Enter the temperature"<<endl;
	while (i <= 7){
		cout<<"Day "<<i<<": ";
		cin>>temp;
		if(temp>=10)	tempMoreThan10++;
		i++;
	}
cout<<"Days with temperature more than 10: "<<tempMoreThan10<<endl;
*/




/*
int a=1,sum=0;
cout<<"\t\t\t\Do...while"<<endl;
while (a!=0){
	cin>>a;
	sum+=a;
}
cout<<endl;
cout<<"SUum: "<<sum<<endl;
*/

int a=1,b=0,n,i=1,sum=0,count=2;
cout<<"\t\t\t\Number of fibonachy"<<endl;
cout<<"Enter the length"<<endl;
cin>>n;
while (i <= n){
	if(0==i%2){
		cout << a << " ";
		sum=sum+a;
		a = a + b;
		count++;
	}
	else{
		cout << b << " "; 	
		sum=sum+b;
		b = a + b;
		count++;
	}
	
	i++;
}
cout<<endl;
cout<<"Sum: "<<sum<<endl;
cout<<"Average: "<<sum*1./(count-2)<<endl;
}