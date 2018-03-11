#include <iostream>
#include <ctime>
using namespace std;

void main(){
srand(time(0));
/*&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&Дві змінні в циклі&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&
cout<<"\t\t\t 2 int in for"<<endl;
for(int i=100, j=0;i>=0;i--, j++){
	cout<<"["<<i<<" "<<j<<"]"<<endl;
}
*/

/*&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&Степінь числа&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&
cout<<"\t\t\t Power();"<<endl;

int number, power,number_power=1;

cout<<"Input number"<<endl;		cin>>number;
cout<<"Input power"<<endl;		cin>>power;

for(int i=0;i<power;i++)		number_power*=number;


cout<<number_power<<endl;

*/

/*&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&do..while(char a!='.');&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&&-_-&
	cout<<"\t\t\t do..while(char a!='.');"<<endl;

	char symbol;
	int count_a=0,count_o=0,count_tab=0;


	cout<<"Input symbol"<<endl;
	do{
		cin>>symbol;	
		if(symbol=='a'||symbol=='A')								count_a++;
		if(symbol=='o'||symbol=='O')								count_o++;
		if(symbol=='.'||symbol=='?'||symbol==','||symbol=='!')		count_tab++;
	}
	while(symbol!='.');


	cout<<"Total entered a: "<<count_a<<endl;
	cout<<"Total entered o: "<<count_o<<endl;
	cout<<"Total entered punctuation marks: "<<count_tab<<endl;
*/

/*				Генератор кидків кубика 2.0
for(int i=0;i<10;i++){
	int a=rand()%6+1;
	switch(a){
	case 1:
	cout<<"\t_____"<<endl;
	cout<<"\t|   |"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t|   |"<<endl;
	cout<<"\t|___|"<<endl;
	break;
	case 2:
	cout<<"\t_____"<<endl;
	cout<<"\t|   |"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t|___|"<<endl;
	break;
	case 3:
	cout<<"\t_____"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t|___|"<<endl;
	break;
	case 4:
	cout<<"\t_____"<<endl;
	cout<<"\t|. .|"<<endl;
	cout<<"\t|   |"<<endl;
	cout<<"\t|. .|"<<endl;
	cout<<"\t|___|"<<endl;
	break;
	case 5:
	cout<<"\t_____"<<endl;
	cout<<"\t|. .|"<<endl;
	cout<<"\t| . |"<<endl;
	cout<<"\t|. .|"<<endl;
	cout<<"\t|___|"<<endl;
	break;
	case 6:
	cout<<"\t_____"<<endl;
	cout<<"\t|...|"<<endl;
	cout<<"\t|   |"<<endl;
	cout<<"\t|...|"<<endl;
	cout<<"\t|___|"<<endl;
	break;
	}
}
*/


	int a=rand()%101,b,count=0,c;
	int mode;

	cout<<"[1] guess bot number"<<endl;
	cout<<"[2] bot guess you number"<<endl;
	cin>>mode;

	switch(mode){
	case 1:

		cout<<"guess bot number"<<endl;
		do{
		cin>>b;
			if(a==b)		break;
			else if(a>b)	cout<<"Bot number more than "<<b<<endl;
			else			cout<<"Bot number less than "<<b<<endl;
			count++;

		}while(a!=b);
		cout<<"You win!"<<endl;
		cout<<"You input wrong numder "<<count<<" times"<<endl;

	break;
	case 2:

		cout<<"You numder?(input from 0 to 100)"<<endl;
		cin>>a;
		b=50;

		for(int i=1;i<100;i++){
			if(a==b)		break;
			else if(a>b)	b=b+(100-b)/2;
			else			b=b-(100-b)/2;
			count++;
		}

		cout<<"Bot win!"<<endl;
		cout<<"Bot input wrong numder "<<count<<" times"<<endl;

	break;
	}

}