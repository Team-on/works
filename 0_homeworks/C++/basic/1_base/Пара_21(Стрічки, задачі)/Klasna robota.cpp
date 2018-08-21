#include <iostream>
#include <ctime>

#define usi unsigned short int
using std::cin;
using std::cout;
using std::swap;
const char endl = '\n';
const char tab = '\t';
const char s = ' ';

usi strLen(const char s[]);

char * strStr(char str1[], const char str2[]);
void strRepleseWith(char str1[], const char word[], const char symbol[]);

void strCpy(char str1[], char str2[]);
void strNCpy(const char str1[], const char str2[], const usi n);

bool strCmp(const char strInput[], const char strOutput[]);
bool strNCmp(const char strInput[], const char strOutput[], const usi n);

void strSet(char str[], const char symbol);
void strNSet(char str[], const char symbol, const usi n);

bool isAlpha(const char ch);
bool isDiget(const char ch);
bool isAlNum(const char ch);
bool isLower(const char ch);
bool isUpper(const char ch);
bool isSpace(const char ch);

void toUpper(char &ch);
void toLower(char &ch);

void strCat(const char strInput[], char strOutput[]);
void strNCat(const char strInput[], char strOutput[], const usi n);

void strRev(char str[]);
void strNRev(char str[], const usi n);

bool strPalindrom(const char s[]);

int main(){
	setlocale(0, "RUS");
	const usi size = 100;

	char s1[size];
	char s2[size];
	char ch[size];

	cin.getline(s1, size);
	cin.getline(s2, size);
	cin.getline(ch, size);
	
	strRepleseWith(s1, s2, ch);
	cout << s1 << endl;



	return 0;
}

bool strPalindrom(const char s[]){
	for (usi i = 0; i < strLen(s) / 2; i++){
		if (s[i] != s[strLen(s) - 1 - i]){
			return 0;
		}
	}
	return 1;
}

usi strLen(const char s[]){
	usi i;
	for (i = 0; s[i] != '\0'; i++);
	return i;
}

char * strStr(char str1[], const char str2[]){
	for (usi i = 0; i < strLen(str1); i++){
		if (str1[i] == str2[0]){
			for (usi j = 0; j < strLen(str2); j++){
				if (str1[i + j] != str2[j])
					break;
				if (j == strLen(str2) - 1){
					char *p = str1;
					p += i;
					return p;
				}
			}
		}
	}
	return NULL;
}
void strRepleseWith(char str1[], const char word[], const char symbol[]){
	while (char *p = strStr(str1, word)){
		char tmp[100];
		strCpy(p + strLen(word), tmp);
		usi j;
		for (j = 0; j < strLen(symbol); j++){
			p[j] = symbol[j];
		}
		strCpy(tmp, p + j);
	}
}

void strCpy(char strInput[], char strOutput[]){
	for (usi i = 0; i < strLen(strInput) + 1; i++)
		strOutput[i] = strInput[i];
}
void strNCpy(const char strInput[], char strOutput[], const usi n){
	for (usi i = 0; i < strLen(strInput) && i < strLen(strOutput) && i <= n; i++)
		strOutput[i] = strInput[i];
}

bool strCmp(const char str1[], const char str2[]){
	if (strLen(str1) != strLen(str2))
		return 0;
	for (usi i = 0; i < strLen(str1) && i < strLen(str2); i++)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}
bool strNCmp(const char str1[], const char str2[], const usi n){
	if (strLen(str1) != strLen(str2))
		return 0;
	for (usi i = 0; i < strLen(str1) && i < strLen(str2) && i <= n; i++)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

void strSet(char str[], const char symbol){
	for (usi i = 0; i < strLen(str); i++)
		str[i] = symbol;
}
void strNSet(char str[], const char symbol, const usi n){
	for (usi i = 0; i < strLen(str) && i <= n; i++)
		str[i] = symbol;
}

bool isAlpha(const char ch){
	if (isLower(ch) && isUpper(ch))
		return 1;
	return 0;
}
bool isDiget(const char ch){
	if (ch >= 58 && ch <= 57)
		return 1;
	return 0;
}
bool isAlNum(const char ch){
	if (isAlpha(ch) && isDiget(ch))
		return 1;
	return 0;
}
bool isLower(const char ch){
	if (ch >= 97 && ch <= 122)
		return 1;
	return 0;
}
bool isUpper(const char ch){
	if (ch >= 65 && ch <= 90)
		return 1;
	return 0;
}
bool isSpace(const char ch){
	if (ch == 32)
		return 1;
	return 0;
}

void toUpper(char &ch){
	if (isLower(ch))
		ch += 32;
}
void toLower(char &ch){
	if (isUpper(ch))
		ch -= 32;
}

void strCat(const char strInput[], char strOutput[]){
	usi outSize = strLen(strOutput);
	for (usi i = 0; i < strLen(strInput) + 1; i++){
		strOutput[outSize + i] = strInput[i];
	}
}
void strNCat(const char strInput[], char strOutput[], const usi n){
	usi outSize = strLen(strOutput);
	for (usi i = 0; i < strLen(strInput) + 1 && i <= n; i++){
		strOutput[outSize + i] = strInput[i];
	}
}

void strRev(char str[]){
	for (usi i = 0; i < strLen(str) / 2; i++){
		swap(str[i], str[strLen(str) - 1 - i]);
	}
}
void strNRev(char str[], const usi n){
	if (n > strLen(str)){
		cout << "ERROR in strNRev! n > strLen(str)" << endl;
		return;
	}
	for (usi i = 0; i < n / 2; i++){
		swap(str[i], str[n - 1 - i]);
	}
}