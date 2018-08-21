#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int

char* translit(char ch) {
	switch (ch) {
	case '�':
		return "a";
	case '�':
		return "b";
	case '�':
		return "v";
	case '�':
		return "g";
	case '�':
		return "d"; 
	case '�':
		return "e";
	case '�':
		return "ye";
	case '�':
		return "ze";
	case '�':
		return "z";
	case '�':
		return "i";
	case '�':
		return "i";
	case '�':
		return "yi";
	case '�':
		return "yi";
	case '�':
		return "k";
	case '�':
		return "l";
	case '�':
		return "m";
	case '�':
		return "n";
	case '�':
		return "o";
	case '�':
		return "p";
	case '�':
		return "r";
	case '�':
		return "s";
	case '�':
		return "t";
	case '�':
		return "u";
	case '�':
		return "f";
	case '�':
		return "x";
	case '�':
		return "c";
	case '�':
		return "ch";
	case '�':
		return "sh";
	case '�':
		return "shch";
	case '�':
		return "b";
	case '�':
		return "yu";
	case '�':
		return "ya";
	case ' ':
		return " ";
	default:
	{
		char str[1] = { ch };
		return str;
	}
		
	}
}

int main(int argc, char * argv[]) {
	FILE * fi, *fo;
	setlocale(0, "RUS");
	const char PRJ_NAME[] = "Project1.exe";
	const char OUTPUT_NAME[] = "out.txt";
	const char INPUT_NAME[] = "in.txt";
	char PATH[_MAX_PATH];   //260
	strcpy(PATH, argv[0]);
	char *p = strstr(PATH, PRJ_NAME);
	strcpy(p, OUTPUT_NAME);
	fo = fopen(PATH, "w");
	strcpy(p, INPUT_NAME);
	fi = fopen(PATH, "r");

	usi FILE_LENGTH = 0;
	while (!feof(fi)) {
		fgetc(fi);
		FILE_LENGTH++;
	}
	fseek(fi, 0, SEEK_SET);

	for (usi i = 0; i < FILE_LENGTH - 1; i++) 
		fprintf(fo, "%s", translit((char)fgetc(fi)));
	
	

	fclose(fo);
	fclose(fi);
	system("pause");
	return 0;
}