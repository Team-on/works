#include <iostream>
using namespace std;

int main()          // #�������.    Code::Blocks ������ main ���� �� int
{
/* �������� 1
int number;
for(;;){
    cout<<"Enter a six-digit number"<<endl;     cin>>number;
    if ((100000<=number&&1000000>number)||(-100000>=number&&-1000000<number)){          //�������� ������� ���� � ����.
        if(number%10+number%100/10+number%1000/100==number/1000%10+number/10000%10+number/100000&&0<number){
//������ �� ���� ��� ������ ���. � ����� ������ �������� ���� ��� � ����� �������? - ��������� �����
            cout<<number<<" is a lucky number"<<endl;
        }
        else cout<<number<<" is an unlucky number"<<endl;
    }
    else if(0==number) cout<<"000000 is a lucky number"<<endl;      //�������� �����
        else cout<<"ERROR\a"<<endl;                                 //��� �������� �����
}
*/

// �������� 2
int number;
char first,second,third,fourth;
for(;;){                                        //����� �� ������� ����� � ����-�� ��� ����!
    cout<<"Enter a four-digit number"<<endl;     cin>>number;
    if ((1000<=number&&10000>number)||(-1000>=number&&-10000<number)){
        first=number/1000;
        if(number<0){                           //���� ����� �����, �� ������� �� ���������� ���� � ����� �����.
            second=-number/100%10;
            third=-number/10%10;
            fourth=-number%10;
        }
        else{                                   // ���� ������ �� ������� � ������ ������ ����� �����
            second=number/100%10;
            third=number/10%10;
            fourth=number%10;
        }
        cout<<int(second)<<int(first)<<int(fourth)<<int(third)<<endl;   // �� �� ������� �������� Char, � �� ��� � ACSII?
    }
    else if(0==number) cout<<"0000"<<endl;      //�� ���� �������, �� � � ������ 1. ��������� �� ������� ����, cout � 0000 � 000000 ��� ���� ���������. �� �� �������� ������� ������� ����? ���� Char? - ����! ��� ������ �� ����, � ���� ������� �� � number �������������� int(first). ������ ����� �� ������. ������ � ���.
        else cout<<"ERROR\a"<<endl;             // ������ ���� �����. � ������ ������ ���������.
}


return 0;
}
