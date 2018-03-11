#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define ESC 27
#define TAB 9
#define ENTER 13
#define SPACE 23

#define ARROW_ALL -32
#define ARROW_UP 72
#define ARROW_RIGHT 77
#define ARROW_DOWN 80
#define ARROW_LEFT 75

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum ConcoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void gotoxy(short x, short y) {
	SetConsoleCursorPosition(hConsole, { x, y });
}

void SetColor(int text = 7, int back = 0) {
	SetConsoleTextAttribute(hConsole, (WORD)((back << 4) | text));
}

int MenuMode(const char *p1, ...) {
	const char **curr;
	char chose = 0, input, size = 0;
	for (curr = &p1; curr[0] != 0; ++curr, ++size);
	system("cls");
	gotoxy(0, 6);
	cout << "Керування стрiлками.\nEnter - вибiр\nESC - Вихiд";
	do {
		for (int i = 0; i < size - 2; ++i) {
			gotoxy(30, 6 + i);
			if (i == chose) {
				SetColor(Yellow);
				cout << '>' << *(&p1 + i);
				SetColor();
			}
			else {
				cout << ' ' << *(&p1 + i);
			}
			cout << endl;
		}

		input = _getch();
		switch (input) {
		case ARROW_ALL:
			input = _getch();
			switch (input) {
			case ARROW_UP:
				--chose;
				break;
			case ARROW_DOWN:
				++chose;
			}
			if (chose < 0)
				chose = size - 3;
			if (chose >= size - 2)
				chose = 0;

			break;
		case ENTER:
			system("cls");
			return chose;
		case ESC:
			system("cls");
			return -1;
		}
	} while (1);
}

#undef ESC
#undef TAB 
#undef ENTER 
#undef SPACE 

#undef ARROW_ALL 
#undef ARROW_UP
#undef ARROW_RIGHT
#undef ARROW_DOWN 
#undef ARROW_LEFT