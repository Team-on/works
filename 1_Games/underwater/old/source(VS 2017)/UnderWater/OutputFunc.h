#pragma once
#include "Includes.h"

enum ConsoleColor{
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

void gotoxy(short x, short y);

// устанавливает цвет текста и подложки в консоли 
void SetColor(ConsoleColor text = (ConsoleColor)GlobalVar::STANDART_TEXT, ConsoleColor background = (ConsoleColor)GlobalVar::STANDART_BACKGROUND);

void PrintLetter(char *text, char chosenLetter, ConsoleColor textColor = Red, ConsoleColor backgroundColor = (ConsoleColor)GlobalVar::STANDART_BACKGROUND);