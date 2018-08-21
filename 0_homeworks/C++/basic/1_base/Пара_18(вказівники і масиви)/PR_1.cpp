#include <iostream>

#define usi unsigned short int
using std::cout;
using std::cin;
const char tab = '\t';
const char s = ' ';
const char endl = '\n';



int main(){
	//int v1, v2;
	//int *p1 = &v1, *p2 = &v2;
	//cin >> v1 >> v2;
	//if (*p1 == *p2)
	//	cout << "Rivni" << endl;
	//else if (*p1 > *p2)
	//	cout << *p1;
	//else
	//	cout << *p2;
	//cout << endl;

	//int v1;
	//int *p1 = &v1;
	//cin >> v1;
	//if (*p1 == 0)
	//	cout << "0";
	//else if (*p1 < 0)
	//	cout << '-' << endl;
	//else
	//	cout << '+';

	//cout << endl;

	//int v1, v2;
	//int *p1 = &v1, *p2 = &v2;
	//cin >> v1 >> v2;
	//int tmp = *p1;
	//*p1 = *p2;
	//*p2 = tmp;
	//cout << *p1 << s << *p2;

	//float v1, v2;
	//char znak;
	//float *p1 = &v1, *p2 = &v2;
	//cin >> v1 >> znak >> v2;
	//switch (znak){
	//case '+':
	//	cout << ( *p1 + *p2 );
	//	break;
	//case '-':
	//	cout << (*p1 - *p2);
	//	break;
	//case '*':
	//	cout << (*p1 * *p2);
	//	break;
	//case '/': case ':':
	//	cout << (*p1 / *p2);
	//	break;
	//default:
	//	cout << "ERROR";
	//}
	//cout << endl;

	//const usi size = 5;
	//int arr[size];
	//int *pArr = arr, *pSum = new int(0);
	//for (usi i = 0; i < size; i++){
	//	cout << (*(pArr + i) = i) << s;
	//	*pSum += *(pArr + i);
	//}
	//cout << endl << *pSum << endl;
	//delete pSum;

	const usi size = 20;
	usi systemChicl;
	usi dec;

		short arr[size] = { 0 };
		cout << "System:" << s;
		cin >> systemChicl;
		cout << "Number" << s;
		cin >> dec;

		usi i = 0;
		while (dec != 0){
			arr[i] = dec % systemChicl;
			dec /= systemChicl;
			++i;
		}

		for (int i = size - 1; i >= 0; i--){
			if (arr[i] != 0 || i == 0){
				for (int j = i; j >= 0; j--){

					if (arr[j] >= 10){
						char abcNum = 65; //A
						for (usi k = 10; k < arr[j]; k++){
							abcNum++;
						}
						cout << abcNum;
					}
					else
						cout << arr[j];

				}
				break;
			}
		}
		cout << endl;


	return 0;
}










