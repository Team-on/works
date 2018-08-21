#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define usi unsigned short int

char* translit(char ch) {
	switch (ch) {
	case 'à':
		return "a";
	case 'á':
		return "b";
	case 'â':
		return "v";
	case 'ã':
		return "g";
	case 'ä':
		return "d"; 
	case 'å':
		return "e";
	case 'º':
		return "ye";
	case 'æ':
		return "ze";
	case 'ç':
		return "z";
	case 'è':
		return "i";
	case '³':
		return "i";
	case 'é':
		return "yi";
	case '¿':
		return "yi";
	case 'ê':
		return "k";
	case 'ë':
		return "l";
	case 'ì':
		return "m";
	case 'í':
		return "n";
	case 'î':
		return "o";
	case 'ï':
		return "p";
	case 'ð':
		return "r";
	case 'ñ':
		return "s";
	case 'ò':
		return "t";
	case 'ó':
		return "u";
	case 'ô':
		return "f";
	case 'õ':
		return "x";
	case 'ö':
		return "c";
	case '÷':
		return "ch";
	case 'ø':
		return "sh";
	case 'ù':
		return "shch";
	case 'ü':
		return "b";
	case 'þ':
		return "yu";
	case 'ÿ':
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