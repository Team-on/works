#include <iostream>
using namespace std;

int main()
{
/*      Завдання 1
char a;
while(1){
cout<<"Input symbol from ASCII table"<<endl;
cin>>a;

    if((a>=65&&a<=90)||(a>=97&&a<=122))                      cout<<a<<" is letter!"<<endl;
    else if(a>=48&&a<=57)                                    cout<<a<<" is number!"<<endl;
    else if((a>=39&&a<=41)||(a>=44&&a<=46)||a==33||a==34||a==58||a==59||a==64||a==91||a==93)    cout<<a<<" is punctuation mark!"<<endl;
    else                                                     cout<<a<<" is other symbol."<<endl;
}
*/

/*      Завдання 3s
char a;
int money, late_number, code_lenght;
cout<<"\t\t\tVasia the programmer"<<endl;
cout<<"Input [1] to calculate code length"<<endl;
cout<<"Input [2] to calculate number of delays"<<endl;
cout<<"Input [3] to calculate amount of money"<<endl;
cin>>a;

    switch(a){
    case '1':
        cout<<"How much money does Vasia want to earn?"<<endl;      cin>>money;
        cout<<"How many times does Vasia want to be late?"<<endl;   cin>>late_number;
        code_lenght=(money+late_number/3*20)*100/50;
        cout<<"Vasia must write "<<code_lenght<<" lines of code."<<endl;
    break;
    case '2':
        cout<<"How many lines of code will Vasia write?"<<endl;     cin>>code_lenght;
        cout<<"How much money does Vasia want to earn?"<<endl;      cin>>money;
        late_number=(code_lenght/100*50-money)*3/20;
        if(code_lenght/100*50<money)          cout<<"Vasia can earn max "<<code_lenght/100*50<<" $."<<endl;
        else if(code_lenght/100*50-money<30)  cout<<"Vasia should not to be late "<<endl;
        else                                  cout<<"Vasia can be late "<<late_number<<" times."<<endl;
    break;
    case '3':
        cout<<"How many lines of code will Vasia write?"<<endl;     cin>>code_lenght;
        cout<<"How many times does Vasia want to be late?"<<endl;   cin>>late_number;
        money=code_lenght/100*50-late_number/3*20;
        if(money>0)              cout<<"Vasia earn "<<money<<"$."<<endl;
        else    if(money==0)     cout<<"Vasia havent salary "<<endl;
        else                     cout<<"Vasia will be fined on "<<-money<<"$."<<endl;
    break;
    default:
        cout<<"ERROR\a"<<endl;
    }
*/

// Завдання 2
char a;
int lenght;
const float taruf=0.35;
const float native_mulltiple=1.5;
const float another_multiple=2;
cout<<"\t\t\tCost of my call"<<endl;
cout<<"Enter call lenght in minutes"<<endl;
cin>>lenght;
cout<<"Input [1] if you called from MTS"<<endl;
cout<<"Input [2] if you called from Kyivstar"<<endl;
cout<<"Input [3] if you called from Beeline"<<endl;
cin>>a;

    switch(a){
    case '1':
            cout<<"Input [1] if you called to MTS"<<endl;
            cout<<"Input [2] if you called to Kyivstar"<<endl;
            cout<<"Input [3] if you called to Beeline"<<endl;
            cin>>a;
        switch(a){
        case '1':
            cout<<"Call cost "<<lenght*taruf<<" grn"<<endl;
        break;
        case '2':
            cout<<"Call cost "<<lenght*taruf*native_mulltiple<<" grn"<<endl;
        break;
        case '3':
            cout<<"Call cost "<<lenght*taruf*another_multiple<<" grn"<<endl;
        break;
        }
    break;
    case '2':
            cout<<"Input [1] if you called to MTS"<<endl;
            cout<<"Input [2] if you called to Kyivstar"<<endl;
            cout<<"Input [3] if you called to Beeline"<<endl;
            cin>>a;
        switch(a){
        case '1':
            cout<<"Call cost "<<lenght*taruf*native_mulltiple<<" grn"<<endl;
        break;
        case '2':
            cout<<"Call cost "<<lenght*taruf<<" grn"<<endl;
        break;
        case '3':
            cout<<"Call cost "<<lenght*taruf*another_multiple<<" grn"<<endl;
        break;
        }
    break;
    case '3':
            cout<<"Input [1] if you called to MTS"<<endl;
            cout<<"Input [2] if you called to Kyivstar"<<endl;
            cout<<"Input [3] if you called to Beeline"<<endl;
            cin>>a;
        switch(a){
        case '1':
            cout<<"Call cost "<<lenght*taruf*another_multiple<<" grn"<<endl;
        break;
        case '2':
            cout<<"Call cost "<<lenght*taruf*another_multiple<<" grn"<<endl;
        break;
        case '3':
            cout<<"Call cost "<<lenght*taruf<<" grn"<<endl;
        break;
        }
    break;
    default:
        cout<<"ERROR\a"<<endl;
    }
return 0;
}
/*


Задание 2. Написать программу подсчета стоимости разговора для разных мобильных
операторов. Пользователь вводит стоимость разговора и выбирает с какого на какой оператор
он звонит. Вывести стоимость на экран.

*/
