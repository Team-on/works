//#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "audiere\\lib\\audiere.lib")
#include "audiere\include\audiere.h"
using namespace audiere;

#include "Includes.h"
#include "MenuFunc.h"
#include "OutputFunc.h"
#include "Game.h"

#include "Mob.h"
#include "Bar.h"

char * GlobalVar::GAMENAME = NULL;
char * GlobalVar::GAMELOCALE = NULL;
char * GlobalVar::PATHTOEXE = NULL;
char *GlobalVar::PATHTOSOUND = NULL;
char *GlobalVar::PATHTOMUSIC = NULL;
int GlobalVar::CONSOLE_SIZE_X = 0;
int GlobalVar::CONSOLE_SIZE_Y = 0;
int GlobalVar::STANDART_TEXT = 7;
int GlobalVar::STANDART_BACKGROUND = 0;
unsigned short int GlobalVar::MUSIC_VOLUME = 127;
unsigned short int GlobalVar::SOUND_VOLUME = 127;


int main(int argc, char * argv[]) {
	//try to load main config file
	{
		cout << "Start..." << endl << endl;

		//Console name
		const char GAMENAMELOC[] = "UnderWater.exe";
		GlobalVar::GAMENAME = new char[strlen(GAMENAMELOC) + 1];
		strcpy(GlobalVar::GAMENAME, GAMENAMELOC);
		GlobalVar::PATHTOEXE = new char[strlen(argv[0]) + 1];
		strcpy(GlobalVar::PATHTOEXE, argv[0]);

		char CONSOLE_NAME[30] = "\0" /*"title "*/;
		strncat(CONSOLE_NAME, GlobalVar::GAMENAME, strlen(GlobalVar::GAMENAME) - 4);
		//system(CONSOLE_NAME);
		SetConsoleTitle(CONSOLE_NAME);
		cout << "Set console name " << CONSOLE_NAME << endl << endl;

		//Load main config file
		char BD_NAME[] = "other.cfg";
		char PATH[_MAX_PATH];
		strcpy(PATH, argv[0]);
		char *p = strstr(PATH, GlobalVar::GAMENAME);
		ifstream fin;
		strcpy(p, BD_NAME);
		fin.open(PATH);
		if (!fin.is_open()) {
			cout << "Cant open " << PATH << endl << endl;
			//return -1;
		}
		else {
			cout << "Open: " << PATH << endl << endl;
		}

		//Lang folder
		char cfgLanguage[10];
		fin >> cfgLanguage;
		GlobalVar::GAMELOCALE = new char[_MAX_PATH];
		strcpy(GlobalVar::GAMELOCALE, "lang\\");
		strcat(GlobalVar::GAMELOCALE, cfgLanguage);
		strcat(GlobalVar::GAMELOCALE, "\\");
		strcpy(p, GlobalVar::GAMELOCALE);
		strcpy(GlobalVar::GAMELOCALE, PATH);
		cout << "Set lang folder: " << PATH << endl;

		//Set console lang
		if (strcmp(cfgLanguage, "UA") == 0)
			strcpy(cfgLanguage, "RUS");
		setlocale(0, cfgLanguage);
		cout << "Set conlose lang: " << cfgLanguage << endl << endl;

		//Console pos
		HWND hwnd;
		char Title[1024];
		GetConsoleTitle(Title, 1024); // Узнаем имя окна
		hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
		MoveWindow(hwnd, 0, 0, 200, 200, TRUE);//xnew,ynew,wnew,hnew -новые положение x,y, ширина и высота
		cout << "Set console pos (0, 0)" << endl;

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

		//Console color
		/*
		0 = Black 8 = Gray
		1 = Blue 9 = Light Blue
		2 = Green A = Light Green
		3 = Aqua B = Light Aqua
		4 = Red C = Light Red
		5 = Purple D = Light Purple
		6 = Yellow E = Light Yellow
		7 = White F = Bright White
		first - back, second - letters
		*/

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

	/*
	cout << "initializing music & sound..." << endl;
	AudioDevicePtr musicDevice = OpenDevice();
	char musicCurrent[_MAX_PATH];
	strcpy(musicCurrent, GlobalVar::PATHTOMUSIC);
	strcat(musicCurrent, "SWAMP.MP3");
	OutputStreamPtr music = OpenSound(musicDevice, musicCurrent, true);
	music->setVolume(float(GlobalVar::MUSIC_VOLUME) / 255);
	music->play();
	music->setRepeat(1);
	//strcpy(musicCurrent, GlobalVar::PATHTOMUSIC);
	//strcat(musicCurrent, "01 Darksiders theme.mp3");
	//OutputStreamPtr sound = OpenSound(musicDevice, musicCurrent, true);
	//sound->setVolume(float(GlobalVar::SOUND_VOLUME) / 255);
	//sound->play();
	*/
	Game game;
	do {
		char menuMain;
		menuMain = MenuInputMain();
		switch (menuMain) {
		case 1:
		{
			char retCode = game.NewGame();
			if (retCode == Game::RETURN_CODES::EXIT) {
				//вийти з гри, чи остатить в меню?
			}
			else if (retCode == Game::RETURN_CODES::PLAYER_CREATED) {
				//Сохранить, начать игру
			}
			system("cls");
		}
		break;
		case 2:
		{
			if(game.player != nullptr)
				game.player->PlayerPrintStats();
		}
		break;
		}
	} while (1);
	

	delete[] GlobalVar::GAMELOCALE;
	delete[] GlobalVar::PATHTOEXE;
	delete[] GlobalVar::GAMENAME;
	delete[] GlobalVar::PATHTOMUSIC;
	delete[] GlobalVar::PATHTOSOUND;
	system("pause");
	return 0;
}











