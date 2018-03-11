#include <iostream>
using namespace std;

#define pi 3.141

#define sum(x) (x + x)
#define SUM(x, y) (y + x)

#define max(x, y)  ((x > y)?x:y)
#define min(x, y)  ((x < y)?x:y)
#define SQR(x)  (x * x)
#define isOdd(x)  ((x % 2 == 0)?0:1)
#define isEven(x)  ((x % 2 == 0)?1:0)

#define maxTrip(x, y, z)  ( (x > y) ? ((x > z) ? x:z) : ((y > z)?y:z) )

#define stepin(x, y) (pow(x, y))

#define Ymova 'a'



void ShowInt(){
	cout << "Int "<< endl;
}//1
void ShowDouble(){
	cout << "Double " << endl;
}

//#define INT			//Аля тумблер. Якщо написати оба, то помилку не викличе, але спрацюэ лише перший в порядку макрос.   
////#define DOUBLE 
//
//#ifdef INT
//	#define show ShowInt
//#endif
//
//#ifdef DOUBLE
//#	define show ShowInt
//#endif     // -1

void main(){
	//cout << sum(10) << endl;
	//cout << SUM(10, 20) << endl;

	//cout << max(1, 2) << endl;
	//cout << min(1, 2) << endl;
	//cout << SQR(2) << endl;
	//cout << isOdd(2) << endl;
	//cout << isEven(2) << endl << endl;

	//cout << maxTrip(2, 1, 3) << endl << endl;

	//cout << stepin(2, 10) << endl << endl;

//	int a = 10;
//#ifdef Ymova
//	a = 20;
//#endif    
//	cout << a << endl;

	//show();             //1

}


