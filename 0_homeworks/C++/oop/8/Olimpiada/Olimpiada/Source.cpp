#include<iostream>
#include<fstream>
#include <Windows.h>
using namespace std;

int strcnt(char *str, char sym) {
	int cnt = 0;
	for (char *p = str; p <= &str[strlen(str) - 1]; p++)
		if (*p == sym)
			++cnt;
	return cnt;
}		

void main(){
	/*
	ifstream fin("file.txt");
	//#define cin fin
		int sizeX, sizeY, towerCnt;
		cin >> sizeX >> sizeY >> towerCnt;
		int *towerX = new int[towerCnt + 2];
		int *towerY = new int[towerCnt + 2];
	
		
		for (int i = 1; i < towerCnt + 1; i++) {
			int x, y;
			cin >> x >> y;
			++x; ++y;
			towerX[i] = x;
			towerY[i] = y;
		}
	#undef cin
		towerX[0] = 0;
		towerY[0] = 0;
		towerX[towerCnt + 1] = sizeX + 1;
		towerY[towerCnt + 1] = sizeY + 1;
		//------------------------
		char **art = new char *[sizeY + 2];
		for (int i = 0; i < sizeY + 2; i++)
			art[i] = new char[sizeX + 2];
		
	
		for (int i = 0; i < sizeY + 2; i++) 
			for (int j = 0; j < sizeX + 2; j++) 
					art[i][j] = '+';

		for (int k = 0; k < towerCnt + 2; k++) 
			for (int i = 0; i < sizeY + 2; i++) 
				for (int j = 0; j < sizeX + 2; j++) 
					if (towerX[k] == j || towerY[k] == i) 
						art[i][j] = '#';
	
		for (int i = 0; i < sizeY + 2; i++){
			for (int j = 0; j < sizeX + 2; j++)
				cout << art[i][j];
			cout << endl;
		}
		//------------
		
		for (int i = 1; i < towerCnt + 1; i++) {
			int minX = i, minY = i;
			for (int j = i; j < towerCnt + 1; j++) {
				if (towerX[minX] > towerX[j])
					minX = j;
				if (towerY[minY] > towerY[j])
					minY = j;
			}
			if (i != minX)
				swap(towerX[i], towerX[minX]);
			if (i != minY)
				swap(towerY[i], towerY[minY]);
		}
	
		int lngX = INT_MIN, lngY = INT_MIN;
		for (int i = 1; i < towerCnt + 2; i++) {
			int curr = towerX[i] - towerX[i - 1];
			if (curr > lngX)
				lngX = curr;
			curr = towerY[i] - towerY[i - 1];
			if (curr > lngY)
				lngY = curr;
		}
		cout << "\n\n B.. "<<(lngY - 1) * (lngX - 1) << endl;
		*/

	///*
	char digit[100];
	cin.getline(digit, 99);
	int *suma = new int[strcnt(digit, '*') + 1];
	for (int i = 0; i < strcnt(digit, '*') + 1; i++)
		suma[i] = 0;
	int counter = 0;
	for (int i = 0; i < strlen(digit); i += 2){
		suma[counter] += int(digit[i] - 48);
		if (digit[i + 1] == '*')
			++counter;
	}
	++counter;
	for (int i = 1; i < counter; i++)
		suma[0] *= suma[i];

	cout << endl << "\tMax : " << suma[0] << endl;

	delete[] suma;
	suma = new int[strcnt(digit, '+') + 1];

	for (int i = 0; i < strcnt(digit, '+') + 1; i++)
		suma[i] = 1;
	counter = 0;
	for (int i = 0; i < strlen(digit); i += 2){
		suma[counter] *= int(digit[i] - 48);
		if (digit[i + 1] == '+')
			++counter;
	}
	++counter;
	for (int i = 1; i < counter; i++)
		suma[0] += suma[i];

	cout << endl << "\tMin : " << suma[0] << endl;
	delete[] suma;
	//*/


	int segment;
	do {
		cout << "Segment: ";
		cin >> segment;
		cout << "Time: ";
		switch (segment) {
		case 8:  cout << "11:11";  break;
		case 9:  cout << "11:17";  break;
		case 10: cout << "17:17";  break;
		case 11: cout << "11:15";  break;
		case 12: cout << "17:15";  break;
		case 13: cout << "17:16";  break;
		case 14: cout << "11:19";  break;
		case 15: cout << "22:17";  break;
		case 16: cout << "22:14";  break;
		case 17: cout << "08:11";  break;
		case 18: cout << "08:17";  break;
		case 19: cout << "08:04";  break;
		case 20: cout << "00:01";  break;
		case 21: cout << "00:07";  break;
		case 22: cout << "00:04";  break;
		case 23: cout << "00:05";  break;
		case 24: cout << "00:00";  break;
		case 25: cout << "08:00";  break;
		case 26: cout << "08:08";  break;
		default: cout << "IMPOSSILE";
		}
		cout << endl;
	} while (segment);

	
	system("pause");
}