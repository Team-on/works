#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;



int main(){
    srand(time(0));

	const short size = 10;

	short a[size], a1[size], c[size], loc_min[size], min_count=0,obmen;

	cout<<"\t\t\tArray 76 and 77"<<endl;

	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%100;
		a1[i]=a[i];
		cout <<setw(3)<< a[i] << "  ";
	}

	cout<<endl<<endl;

	for (int i = 1; i < size-1; i++)
	{
		if(a[i]<a[i-1]&&a[i]<a[i+1])
			a1[i]*=a[i];

        else if(a[i]>a[i-1] && a[i]>a[i+1])
           a1[i]=0;
	}

	cout<<endl;

    for (int i = 0; i < size; i++)
		cout <<setw(3)<< a1[i] << "  ";


    cout<<"\n\n\n\n\t\t\tArray 53\n"<<endl;


    cout<<"\t\ti \t A \t B \t C\n"<<endl;
    for (int i = 0; i < size; i++)
	{
		a[i] = rand()%100;
		a1[i]= rand()%100;

		if(a[i]>a1[i])
            c[i]=a[i];
        else
            c[i]=a1[i];

		cout <<"\t\t"<<i<<"\t"<< a[i] << "\t"<<a1[i]<<"\t"<<c[i]<<endl;
	}



return 0;}
