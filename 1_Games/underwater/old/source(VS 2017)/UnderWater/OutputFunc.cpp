#pragma once
#include "OutputFunc.h"


HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(short x, short y) {
	//COORD  coord = { x, y };
	SetConsoleCursorPosition(CONSOLE_HANDLE, { x, y });
}

void SetColor(ConsoleColor text, ConsoleColor background) {
	SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((background << 4) | text));
}

//Print one letter BIG and with other color
void PrintLetter(char *text, char chosenLetter, ConsoleColor textColor, ConsoleColor backgroundColor) {
	bool firstChosen = 0;
	for (int i = 0; i < strlen(text); i++) {
		if (firstChosen == 0 && (text[i] == tolower(chosenLetter) || text[i] == toupper(chosenLetter) ) ) {
			SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((backgroundColor << 4) | textColor));
			cout << (char)toupper(text[i]);
			SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((GlobalVar::STANDART_BACKGROUND << 4) | GlobalVar::STANDART_TEXT));
			firstChosen = 1;
		}
		else {
			cout << text[i];
		}
	}
}