#include <iostream>
using namespace std;

int main()
{
setlocale(0,"RUS");
//  �������� 1
short R1,R2,R3;
cout <<"\t�������� �� ���������� ���������� ����� ��� ������������ �i��������i"<<endl;
cout <<"R1= "; cin>>R1;
cout <<"R2= "; cin>>R2;
cout <<"R3= "; cin>>R3;
cout <<"R0= "<<1./R1+1./R2+1./R3;


/*  �������� 3
short v,t,a;
cout <<"\t�������� �� ���������� �������� �i�����i"<<endl;
cout <<"v= "; cin>>v;
cout <<"t= "; cin>>t;
cout <<"a= "; cin>>a;
cout <<"S= "<<v*t+(a*t*t);
*/

/*  �������� 2
float l,r;
const float Pi=3.14;
cout <<"\t�������� �� ���������� ����i ����� ��� �i���i� ������i �����"<<endl;
cout <<"L= "; cin>>l;
r=l/(2*Pi);
cout <<"S= "<<Pi*r*r;
*/
return 0;
}
