#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

void main(){

	srand(time(0));

/*	Злиття двох масивів
	const short size = 5;

	short a[size], b[size], c[size * 2];


	cout << "A:" << endl;
	for (int i = 0; i < size; i++)
	{
		a[i] = 0;
		b[i] = 1;
		cout << "a["<<i+1<<"] = "<<a[i]<<"\n";
	}

	cout << endl << "B:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "b[" << i+1 << "] = " << b[i] << "\n";
	}


	for (int i = 0; i < size; i++)
	{
		c[i + i] = a[i];
		c[i + i + 1] = b[i];
	}


	cout << endl << "C:" << endl;
	for (int i = 0; i < size*2; i++)
	{
		cout << "c[" << i+1 << "] = " << c[i] << "\n";
	}
*/

/*
	const short size = 5;

	short a[size];
	float b[size];


	cout << "A:\t\tB:" << endl;
	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%20+1;
		if(a[i]>5)
			b[i]=a[i]/2.;
		else
			b[i]=a[i]*2;
		cout << "a["<<i+1<<"] = "<<a[i]<<"\t";
		cout << "b[" << i+1 << "] = " << b[i] << "\n";
	}
*/

/*
	const short size = 5;

	short a[size];
	float average_a=0, b[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%20+1;
		cout << "a["<<i+1<<"] = "<<a[i]<<"\n";
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			average_a += a[j];
		}
		average_a /= size-i;
		b[i] = average_a;
		average_a = 0;
	}

	cout<<endl;

	for (int i = 0; i < size; i++)
	{
		cout << "b[" << i+1 << "] = " << b[i] << "\n";
	}
*/

/*
	const short size = 5;

	short a[size];
	float sum_a=0, b[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%10;		
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = i; j >= 0; j--)
		{
			sum_a += a[j];
		}
		b[i] = sum_a;
		sum_a = 0;
	}


	for (int i = 0; i < size; i++)
	{
		cout << "a["<<i+1<<"] = "<<a[i]<<"\t";
		cout << "b[" << i+1 << "] = " << b[i] << "\n";
	}
*/

	/*const short size_dop = 5;

	short a[size_dop], b[size_dop], c[size_dop], count_plus=0, count_minus=0;

	for (int i = 0; i < size_dop; i++)
	{
		a[i] = rand()%21-10;	
		b[i]=0;
		c[i]=0;
	}

	for (int i = 0; i < size_dop; i++)
	{
		if(a[i]>0){
			b[count_plus]=a[i];
			count_plus++;
		}
		else if(a[i]<0){
			c[count_minus]=a[i];
			count_minus++;
		}
	}*/





/*
	const short size = 20;

	short a[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%100+1;	
		cout << a[i] << "  ";
	}

	cout<<endl<<endl;

	for (int i = 1; i < size-1; i++)
	{
		if(a[i]<a[i-1]&&a[i]<a[i+1]){
			cout<<"Loc min: "<<a[i]<<" Pos: "<<i+1<<endl;
		}
	}
*/

/* Local min and max
	const short size = 20;

	short a[size], loc_min[size], min_count=0;

	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%100+1;	
		cout << a[i] << "  ";
	}

	cout<<endl<<endl;

	for (int i = 1; i < size-1; i++)
	{
		if(a[i]<a[i-1]&&a[i]<a[i+1]){
			loc_min[min_count]=a[i];
			cout<<"Loc min: "<<loc_min[min_count]<<" Pos: "<<i+1<<endl;
			min_count++;
		}
	}

	cout<<endl;

	for (int i = 1; i < min_count; i++)
	{
		if(loc_min[0]>loc_min[i]){
			loc_min[0]=loc_min[i];
		}
	}

	cout<<"Min of min: "<<loc_min[0]<<endl;




	cout<<endl<<endl;
	min_count=0;

	for (int i = 1; i < size-1; i++)
	{
		if(a[i]>a[i-1] && a[i]>a[i+1]){
			loc_min[min_count]=a[i];
			cout<<"Loc max: "<<loc_min[min_count]<<" Pos: "<<i+1<<endl;
			min_count++;
		}
	}

	cout<<endl;

	for (int i = 1; i < min_count; i++)
	{
		if(loc_min[0]<loc_min[i]){
			loc_min[0]=loc_min[i];
		}
	}

	cout<<"Max of max: "<<loc_min[0]<<endl;
	
*/

/*	
const short size = 10;

	short a[size], e, rozn,el,num;

	for (int i = 0; i < size; i++)
	{
		a[i] = rand()%201-100;	
		cout << a[i] << "  ";
	}


	cout<<endl<<endl;
	
	cout<<"Enter e"<<endl;
	cin>>e;

	rozn=a[0]-e;
	el=a[0];
	num=0;

	for (int i = 1; i < size; i++)
	{
		if(abs(rozn)>abs(a[i]-e)){
			rozn=a[i]-e;
			el=a[i];
			num=i;
		}
	}
	cout<<el<<" #"<<num+1<<endl;
*/

	const short size = 6;

	short b[size], a[size], obmen;


	for (int i = 0; i < size; i++)
	{
		a[i] = i%2;	
		cout << a[i] << "  ";
	}


	cout<<endl<<endl;



	for (int i = 0; i < size; i+=2)
	{
		a[i]+=a[i+1];
		a[i+1]=a[i]-a[i+1];
		a[i]=a[i]-a[i+1];

		cout << a[i] << "  "<< a[i+1] << "  ";
	}



	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;





	for (int i = 0; i < size; i++)
	{
		b[i] = i;	
		cout << b[i] << "  ";
	}


	cout<<endl<<endl;
	



	for (int i = 0; i < size/2; i++)
	{
		obmen=b[i];
		b[i]=b[size-i-1];
		b[size-i-1]=obmen;
	}

	for (int i = 0; i < size; i++)
	{
		cout << b[i] << "  ";
	}

	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;





	for (int i = 0; i < size; i++)
	{
		b[i] = i;	
		cout << b[i] << "  ";
	}


	cout<<endl<<endl;
	



	for (int i = 0; i < size/2; i++)
	{
		obmen=b[i];
		b[i]=b[size/2+i];
		b[size/2+i]=obmen;
	}

	for (int i = 0; i < size; i++)
	{
		cout << b[i] << "  ";
	}

//
}