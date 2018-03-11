#include <iostream>

using namespace std;

int main()
{
setlocale(0,"RUS");
/*
float x,y;
    cout <<"¬ведiть вiдстань до аеропорту"<< endl;
    cin>>x;
    cout <<"¬ведiть час(у годинах)"<< endl;
    cin>>y;
    if(0==x||0==y)
        cout << "¬и ввели 0" << endl;
    else cout << "“реба њхати зi швидкiстю "<<x/y<<" км/год"<< endl;
*/

/*
unsigned short x,c,xk,ck;
float gk,g;
const int china = 30;
    cout <<"¬ведiть час початку розмови у форматi год хв сек"<< endl;
    cin>>g>>x>>c;
     cout <<"¬ведiть час кiнц€ розмови у форматi год хв сек"<< endl;
    cin>>gk>>xk>>ck;

    g=g*60+x+c/60.;        //переводжу час в хвидини
    gk=gk*60+xk+ck/60.;
    if(gk==g)
        cout << "÷е розмова на весь день, i вона коштуЇ "<<(24*60*china)/100<<" грн"<<endl;
    else {gk>g?g=(gk-g)*china:g=(24*60-g+gk)*china;
    if(g<100) cout<<"÷iна розмови "<<g<<" коп"<<endl;
    else cout<<"÷iна розмови "<<g/100<<" грн"<<endl;
    }
*/

float l,r,c1,c2,c3,f1,f2,f3;
const int china = 30;
    cout <<"¬ведiть вiстань"<< endl;
    cin>>l;
     cout <<"¬ведiть розхiд бензину на 100 км"<< endl;
    cin>>r;
      cout <<"¬ведiть цiну бензину є1"<< endl;
    cin>>c1;
      cout <<"¬ведiть цiну бензину є2"<< endl;
    cin>>c2;
      cout <<"¬ведiть цiну бензину є3"<< endl;
    cin>>c3;

f1=l/100*c1*r;
f2=l/100*c2*r;
f3=l/100*c3*r;
cout <<"Ѕензин за цiною\t\t"<<c1<<"\t"<<c2<<"\t"<<c3<<endl;
cout <<"¬артiсть поњздки\t"<<f1<<"\t"<<f2<<"\t"<<f3<<endl;
return 0;
}

