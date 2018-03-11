#include <iostream>

#define usi unsigned short int 
using namespace std;

void strNRev(char str[], const usi n);
bool strPalindrom(const char s[]);
long long atofMy(const char s[]);
double atoiMy(const char s[]);

bool isDuskiRight(const char s[]);

void cryptZhezar(char *s, const usi key);
void decryptZhezar(char * s, const usi key);

void cryptWiendger(char *s, const char * key);
void decryptWiendger(char * s, const char * key);

int main () {
	const usi size = 100;
	char s1[size];
	char s2[size];
	


	//Шифрування 1
	char key[100];
	cin.getline(s1, size);
	cin >> key;
	cryptWiendger(s1, key);
	cout << s1 << endl;
	decryptWiendger(s1, key);
	cout << s1 << endl;


	//Шифрування 2
	//usi key;
	//cin.getline(s1, size);
	//cin >> key;
	//cryptZhezar(s1, key);
	//cout << s1 << endl;
	//decryptZhezar(s1, key);
	//cout << s1 << endl;

	//cin.getline(s2, size);

	//Reverse chosen word
	//if (strPalindrom(s2) != 1){
	//	while (char *p = strstr(s1, s2)){
	//		usi wordSize = strlen(s2);
	//		strNRev(p, wordSize);
	//	}
	//	cout << s1 << endl;
	//}
	//else
	//	cout << "Palindrom" << endl;


	return 0;
}

void cryptZhezar(char *s, const usi key){
	for (usi i = 0; i < strlen(s); i++){
		if (isalpha(s[i])){
			if (s[i] + key > 'z')
				s[i] = s[i] - 26 + (key % 26 + 1);
			else if (s[i] + key < 'a')
				s[i] = s[i] + 26 + (key % 26 + 1);
			else
				s[i] += key;
		}
	}
}
void decryptZhezar(char *s, const usi key){
	for (usi i = 0; i < strlen(s); i++){
		if (isalpha(s[i])){
			if (s[i] - key > 'z')
				s[i] = s[i] - 26 - (key % 26 + 1);
			else if (s[i] - key < 'a')
				s[i] = s[i] + 26 - (key % 26 + 1);
			else
				s[i] -= key;
		}
	}
}

void cryptWiendger(char *s, const char * key){
	usi j = 0;
	for (usi i = 0; i < strlen(s); i++){
		if (j >= strlen(key))
			j = 0;
		if (isalpha(s[i])){
			if (s[i] + (key[j] - 97) > 'z')
				s[i] = s[i] + (key[j] - 97) - 26;
			else
				s[i] += (key[j] - 97);
			++j;
		}
	}
}

//Не робе
void decryptWiendger(char * s, const char * key){
	usi j = 0;
	for (usi i = 0; i < strlen(s); i++){
		if (j >= strlen(key))
			j = 0;
		if (isalpha(s[i])){
			if (s[i] - (key[j] - 97) > 'z')
				s[i] = s[i] - (key[j] - 97) - 26;
			else
				s[i] -= (key[j] - 97);
			++j;
		}
	}
} 

bool isDuskiRight(const char s[]){
	char s2[100];
	strcpy(s2, s);

	for (usi i = 0; i < strlen(s2); i++){
		if (!(s2[i] == '(' || s2[i] == '{' || s2[i] == '[' || s2[i] == ')' || s2[i] == '}' || s2[i] == ']'))
			s2[i] = ' ';
	}

	for (usi i = 0; i < strlen(s2); i++){
		cout << "S2: " << s2 << endl;
		if (s2[i] == '(' || s2[i] == '{' || s2[i] == '['){
			char dyzka = s2[i];
			if (dyzka == '(')
				++dyzka;
			else 
				dyzka += 2;
			bool in = 0;
			for (usi j = i + 1; j < strlen(s2); j++){
				if (s2[j] == '(' || s2[j] == '{' || s2[j] == '['){
					in = 1;
				}
				if (s2[j] == ')' || s2[j] == '}' || s2[j] == ']'){
					in = 0;
				}
				if (s2[j] == dyzka){
					s2[i] = ' ';
					s2[j] = ' ';
					if (in == 1)
						return 0;
					break;
				}
				if (j == strlen(s2) - 1)
					return 0;
				else if (in == 1)
					return 0;
			}
		}
	}
	for (usi i = 0; i < strlen(s2); i++){
		if (s2[i] != ' ')
			return 0;
	}
	return 1;
}

void strNRev(char str[], const usi n){
	if (n > strlen(str)){
		cout << "ERROR in strNRev! n > strLen(str)" << endl;
		return;
	}
	for (usi i = 0; i < n / 2; i++){
		swap(str[i], str[n - 1 - i]);
	}
}

bool strPalindrom(const char s[]){
	for (usi i = 0; i < strlen(s) / 2; i++){
		if (s[i] != s[strlen(s) - 1 - i]){
			return 0;
		}
	}
	return 1;
}

long long atofMy(const char s[]){
	usi i = 0, numCnt = -1;
	long long buf = 0;

	while (s[i] != '\0'){
		if (s[i] >= '0' &&  s[i] <= '9')
			++numCnt;
		++i;
	}

	i = 0;
	while (s[i] != '\0'){
		if (s[i] >= '0' &&  s[i] <= '9'){
			buf += (s[i] - 48) * pow(10, numCnt);
			--numCnt;
		}
		++i;
	}
	return buf;
}

double atoiMy(const char s[]){
	usi i = 0, numCnt = -1;
	double buf = 0;

	while (s[i] != '\0'){
		if (s[i] >= '0' &&  s[i] <= '9')
			++numCnt;
		++i;
	}

	i = 0;
	while (s[i] != '\0'){
		if (s[i] >= '0' &&  s[i] <= '9'){
			buf += (s[i] - 48) * pow(10, numCnt);
			--numCnt;
		}
		++i;
	}
	return buf;
}