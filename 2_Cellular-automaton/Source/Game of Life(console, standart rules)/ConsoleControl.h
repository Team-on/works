#ifndef _HEADER_CONSOLE_CONTROL_H_
#define _HEADER_CONSOLE_CONTROL_H_
#include "Includes.h"

struct ConcoleColorCl {
	int Black = 0,
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
		White = 15;
};
class ConcoleColorStyle {
	int text, background;
public:
	ConcoleColorStyle(){
		text = background = 0;
	}
	ConcoleColorStyle(int txt, int back) {
		text = txt; 
		background = back;
	}
	ConcoleColorStyle(ConcoleColorStyle &rhs) {
		text = rhs.text;
		background = rhs.background;
	}
	friend class ConsoleControl;
} STYLE_STANDART(0, 7);

class ConsoleControl {
	static HANDLE hConsole;
	static HWND hwnd;
public:
	static ConcoleColorCl ConsoleColor;

	ConsoleControl() {}
	~ConsoleControl() {}

	static void gotoxy(short x, short y) {
		SetConsoleCursorPosition(hConsole, { x, y });
	}
	static void Pause() {
		system("pause");
	}

	static void SetColor(ConcoleColorStyle style = STYLE_STANDART) {
		SetConsoleTextAttribute(hConsole, (WORD)((style.background << 4) | style.text));
	}
	static void SetColor(int text, int back = 0) {
		SetConsoleTextAttribute(hConsole, (WORD)((back << 4) | text));
	}

	static void SetStyle(ConcoleColorStyle style = STYLE_STANDART) {
		char command[9] = "color ";	
		if (style.text >= 0 && style.text <= 9) {
			char tmp[2] = { style.text + 48, 0 };
			strcat(command, tmp);
		}
		else {
			char tmp[2] = { style.text + 55 , 0 };
			strcat(command, tmp);
		}
		if (style.background >= 0 && style.background <= 9) {
			char tmp[2] = { style.background + 48, 0 };
			strcat(command, tmp);
		}
		else {
			char tmp[2] = { style.background + 55 , 0 };
			strcat(command, tmp);
		}
		system(command);
	}

	static void SetTitle(char *title) {
		SetConsoleTitleA(title);
	}
	static char * GetTitle() {
		char *Title = new char[100];
		GetConsoleTitle(Title, 99);
		return Title;
	}
	static void SetLoc(char *loc) {
		setlocale(LC_ALL, loc);
	}
	static void SetLang(char *loc) {
		setlocale(LC_ALL, loc);
	}

	static void SetPos() {
		MoveWindow(hwnd, 5, 5, 200, 800, TRUE);
		cout << "Set console pos (0, 0)" << endl;
	}
	
	/*{
	//Console pos
	

	//Console size
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD maxWindow = GetLargestConsoleWindowSize(out_handle); // размер самого большого возможного консольного окна

	char consoleSizeX[5], consoleSizeY[5];
	fin >> consoleSizeX >> consoleSizeY;
	if (strcmp(consoleSizeX, "MAX") == 0) {
		GlobalVar::CONSOLE_SIZE_X = maxWindow.X - 4;
		//maxWindow.X = GlobalVar::CONSOLE_SIZE_X;
	}
	else {
		GlobalVar::CONSOLE_SIZE_X = atoi(consoleSizeX);
		if (maxWindow.X - 4 < GlobalVar::CONSOLE_SIZE_X) {
			GlobalVar::CONSOLE_SIZE_X = maxWindow.X - 4;
		}
		else {
			maxWindow.X = GlobalVar::CONSOLE_SIZE_X;
		}
	}
	if (strcmp(consoleSizeY, "MAX") == 0) {
		GlobalVar::CONSOLE_SIZE_Y = maxWindow.Y - 2;
		//maxWindow.Y = GlobalVar::CONSOLE_SIZE_Y;
	}
	else {
		GlobalVar::CONSOLE_SIZE_Y = atoi(consoleSizeY);
		if (maxWindow.Y - 2 < GlobalVar::CONSOLE_SIZE_Y) {
			GlobalVar::CONSOLE_SIZE_Y = maxWindow.Y - 4;
		}
		else {
			maxWindow.Y = GlobalVar::CONSOLE_SIZE_Y;
		}
	}

	cout << "Set window size: " << GlobalVar::CONSOLE_SIZE_X << " " << GlobalVar::CONSOLE_SIZE_Y << endl;
	SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 4, maxWindow.Y - 2 };
	SMALL_RECT minWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(out_handle, true, &minWindow);

	//Console buffer
	maxWindow.Y -= 2;
	maxWindow.Y *= 10;
	maxWindow.X *= 2;
	cout << "Set window buffer: " << maxWindow.X << " " << maxWindow.Y << endl;
	SetConsoleScreenBufferSize(out_handle, maxWindow);
	SetConsoleWindowInfo(out_handle, true, &srctWindow);

	fin >> GlobalVar::STANDART_BACKGROUND >> GlobalVar::STANDART_TEXT;

	char CONSOLE_COLOR[20] = "color ";
	char CONSOLE_COLOR_TEXT[2], CONSOLE_COLOR_BACKGROUND[2];

	itoa(GlobalVar::STANDART_BACKGROUND, CONSOLE_COLOR_BACKGROUND, 16);
	itoa(GlobalVar::STANDART_TEXT, CONSOLE_COLOR_TEXT, 16);
	strcat(CONSOLE_COLOR, CONSOLE_COLOR_BACKGROUND);
	strcat(CONSOLE_COLOR, CONSOLE_COLOR_TEXT);

	system(CONSOLE_COLOR);
	cout << "Set console " << CONSOLE_COLOR << endl << endl;

	//Music init
	fin >> GlobalVar::MUSIC_VOLUME;
	GlobalVar::PATHTOMUSIC = new char[_MAX_PATH];
	GlobalVar::PATHTOSOUND = new char[_MAX_PATH];
	strcpy(PATH, argv[0]);
	p = strstr(PATH, GlobalVar::GAMENAME);
	strcpy(p, "sounds\\music\\");
	strcpy(GlobalVar::PATHTOMUSIC, PATH);
	cout << "Music init: " << GlobalVar::PATHTOMUSIC << endl;
	strcpy(p, "sounds\\");
	strcpy(GlobalVar::PATHTOSOUND, PATH);
	cout << "Sound init: " << GlobalVar::PATHTOSOUND << endl << endl;

	//Other
	srand(time(0));
	cout << "Init random" << endl << endl;

	//system("pause");
	Sleep(500);
	system("cls");
	fin.close();
}
	*/
};


#endif