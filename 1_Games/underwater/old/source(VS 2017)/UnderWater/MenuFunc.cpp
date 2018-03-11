#include "Includes.h"
#include "MenuFunc.h"
#include "OutputFunc.h"


#define ESC 27
#define TAB 9
#define ENTER 13
#define SPACE 23

#define ARROW_ALL -32
#define ARROW_UP 72
#define ARROW_RIGHT 77
#define ARROW_DOWN 80
#define ARROW_LEFT 75

//return 1 - New game, 2 - load game
char MenuInputMain() {
	HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	char menuMain;
	short int menuMainPos = 1;

	do {
		gotoxy(0, 0);
		SetColor(White, Blue);
		if (menuMainPos == 1) {
			SetColor(LightMagenta, Blue);
			cout << "\t\tNew Game \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "\t\tNew Game \t\t";
		if (menuMainPos == 2) {
			SetColor(LightMagenta, Blue);
			cout << "Load Game \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Load Game \t\t";
		if (menuMainPos == 3) {
			SetColor(LightMagenta, Blue);
			cout << "Config \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Config \t\t";
		if (menuMainPos == 4) {
			SetColor(LightMagenta, Blue);
			cout << "Help \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Help \t\t";
		if (menuMainPos == 5) {
			SetColor(LightMagenta, Blue);
			cout << "Exit \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Exit \t\t";
		
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << endl;
		SetColor(LightGray, Black);
		menuMain = getch();
		if(
			menuMain == ENTER ||
			menuMain == '?'
			)
			system("cls");

		if (menuMain == ESC)
			exit(0);

		switch (menuMain) {
		case ARROW_ALL:
			menuMain = getch();
			switch (menuMain) {
			case ARROW_LEFT:
				menuMainPos--;
			break;
			case ARROW_RIGHT:
				menuMainPos++;
			break;
			}
		break;
		case ENTER:
			switch (menuMainPos) {
			case 1:
				return 1;
			break;
			case 2:
				return 2;
			break;
			case 3:
				MenuInputConfig();
			break;
			case 4:
				{
				REPEAT_HELP_FOR_VERY_SMART_TESTERS:
				gotoxy(0, 2);
				char PATH[_MAX_PATH];
				ifstream fin;
				
				strcpy(PATH, GlobalVar::GAMELOCALE);
				strcat(PATH, "main_menu.help");

				fin.open(PATH);
				if (!fin.is_open()) {
					cout << "Cant open: " << PATH << endl;
				}
				unsigned long long FILE_LENGTH = 0;
				for (FILE_LENGTH = 0; fin.peek() != EOF; FILE_LENGTH++) {
					fin.get();
				}
				fin.seekg(0);
				char *help = new char[FILE_LENGTH + 1];
				for (unsigned long long i = 0; fin.peek() != EOF; i++) {
					help[i] = fin.get();
				}
				help[FILE_LENGTH] = '\0';
				cout << endl << help << endl << endl;

				fin.close();
				delete[] help;
			}
			break;
			case 5:
				exit(0);
			break;
			}
		break;
		case '?':
			goto REPEAT_HELP_FOR_VERY_SMART_TESTERS;
		break;
		default:

		break;
		}

		if (menuMainPos >= 6)
			menuMainPos = 1;
		else if (menuMainPos <= 0)
			menuMainPos = 5;
	} while (1);

	return menuMain;
}

//return 1 - back
char MenuInputConfig() {
	HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	char menuMain = ENTER;
	short int menuMainPos = 1;

	do {
		gotoxy(0, 0);
		SetColor(White, Blue);
		if (menuMainPos == 1) {
			SetColor(LightMagenta, Blue);
			cout << "\t\tLanguage \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "\t\tLanguage \t\t";
		if (menuMainPos == 2) {
			SetColor(LightMagenta, Blue);
			cout << "Colors \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Colors \t\t";
		if (menuMainPos == 3) {
			SetColor(LightMagenta, Blue);
			cout << "Music \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Music \t\t";
		if (menuMainPos == 4) {
			SetColor(LightMagenta, Blue);
			cout << "Sound \t\t";
			SetColor(White, Blue);
		}
		else {
			//SetColor(Black, Blue);
			cout << "Sound \t\t";
			//SetColor(White, Blue);
		}
		if (menuMainPos == 5) {
			SetColor(LightMagenta, Blue);
			cout << "Help \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Help \t\t";
		if (menuMainPos == 6) {
			SetColor(LightMagenta, Blue);
			cout << "Back \t\t";
			SetColor(White, Blue);
		}
		else
			cout << "Back \t\t";

		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" << endl;
		SetColor(LightGray, Black);

		if (menuMain == ENTER && menuMain != '?' && menuMainPos != 5) {
			gotoxy(0, 1);
			for (int i = 0; i < 20; i++) {
					cout << "                                                                                          ";
				cout << endl;
			}
			gotoxy(0, 1);
		}
		menuMain = getch();
		if (menuMain == ESC)
			exit(0);
		if (menuMain == ENTER && menuMain != '?' && menuMainPos != 5) {
			gotoxy(0, 1);
			for (int i = 0; i < 20; i++) {
					cout << "                                                                                          ";
				cout << endl;
			}
			gotoxy(0, 1);
		}

		switch (menuMain) {
		case ARROW_ALL:
			menuMain = getch();
			switch (menuMain) {
			case ARROW_LEFT:
				menuMainPos--;
				break;
			case ARROW_RIGHT:
				menuMainPos++;
				break;
			}
		break;
		case ENTER:
			switch (menuMainPos) {
			case 1:
			{
				SetColor(LightMagenta, Blue);
				cout << "\t\t\t\t" << endl;
				char BD_NAME[] = "other.cfg";
				char PATH[_MAX_PATH];
				strcpy(PATH, GlobalVar::PATHTOEXE);
				char *p = strstr(PATH, GlobalVar::GAMENAME);
				ifstream fin;
				strcpy(p, BD_NAME);
				fin.open(PATH);
				if (!fin.is_open()) {
					cout << "Cant open " << PATH << endl << endl;
					//return -1;
				}
				char cfgLanguage[10];
				fin >> cfgLanguage;
				fin.close();

				int langPos = 1;
				char langInput;
				do {
					bool needToExit = 0;

					if (langPos == 1) {
						SetColor(LightMagenta, Blue);
						cout << "\t\tUkrainian\t" << endl;
						SetColor(White, Blue);
					}
					else {
						if (strcmp(cfgLanguage, "UA") == 0) {
							SetColor(Yellow, Blue);
							cout << "\t\tUkrainian\t" << endl;
							SetColor(White, Blue);
						}
						else {
							cout << "\t\tUkrainian\t" << endl;
						}
					}
					if (langPos == 2) {
						SetColor(LightMagenta, Blue);
						cout << "\t\tRussian\t\t" << endl;
						SetColor(White, Blue);
					}
					else {
						if (strcmp(cfgLanguage, "RUS") == 0) {
							SetColor(Yellow, Blue);
							cout << "\t\tRussian\t\t" << endl;
							SetColor(White, Blue);
						}
						else {
							cout << "\t\tRussian\t\t" << endl;
						}
					}
					if (langPos == 3) {
						SetColor(LightMagenta, Blue);
						cout << "\t\tEnglish\t\t" << endl;
						SetColor(White, Blue);
					}
					else {
						if (strcmp(cfgLanguage, "ENG") == 0) {
							SetColor(Yellow, Blue);
							cout << "\t\tEnglish\t" << endl;
							SetColor(White, Blue);
						}
						else {
							cout << "\t\tEnglish\t\t" << endl;
						}
					}
					if (langPos == 4) {
						SetColor(LightMagenta, Blue);
						cout << "\t\tBack\t\t" << endl;
						SetColor(White, Blue);
					}
					else {
						cout << "\t\tBack\t\t" << endl;
					}

					langInput = getch();
					if (langInput == ESC)
						exit(0);
					gotoxy(0, 2);

					switch (langInput) {
					case ARROW_ALL:
						langInput = getch();
						switch (langInput) {
						case ARROW_UP:
							langPos--;
							break;
						case ARROW_DOWN:
							langPos++;
							break;
						}
					break;
					case ENTER: {
						ofstream fout;
						fout.open(PATH);
						switch (langPos) {
						case 1:
							fout << "UA" << endl;
							strcpy(cfgLanguage, "UA");
						break;
						case 2:
							fout << "RUS" << endl;
							strcpy(cfgLanguage, "RUS");
						break;
						case 3:
							fout << "ENG" << endl;
							strcpy(cfgLanguage, "ENG");
						break;
						case 4:
							fout << cfgLanguage << endl;
						break;
						}
						fout << "MAX MAX" << endl;
						fout << GlobalVar::STANDART_BACKGROUND << " " << GlobalVar::STANDART_TEXT << endl;
						fout << GlobalVar::MUSIC_VOLUME << " " << GlobalVar::SOUND_VOLUME;
						fout.close();
						if (langPos != 4) {
							HWND hwnd;
							hwnd = FindWindow(NULL, GlobalVar::GAMENAME);
							ShellExecute(hwnd, "open", GlobalVar::PATHTOEXE, NULL, NULL, SW_MAXIMIZE);
							exit(0);
						}
						else {
							needToExit = 1;
							break;
						}
					}
					break;
					case '?':
					{
						gotoxy(1, 5);
						SetColor(LightGray);
						char PATH[_MAX_PATH];
						ifstream fin;

						strcpy(PATH, GlobalVar::GAMELOCALE);
						strcat(PATH, "config_menu_lang.help");

						fin.open(PATH);
						if (!fin.is_open()) {
							cout << "Cant open: " << PATH << endl;
						}
						unsigned long long FILE_LENGTH = 0;
						for (FILE_LENGTH = 0; fin.peek() != EOF; FILE_LENGTH++) {
							fin.get();
						}
						fin.seekg(0);
						char *help = new char[FILE_LENGTH + 1];
						for (unsigned long long i = 0; fin.peek() != EOF; i++) {
							help[i] = fin.get();
						}
						help[FILE_LENGTH] = '\0';
						cout << endl << help << endl << endl;

						fin.close();
						delete[] help;
						gotoxy(0, 2);
						SetColor(LightMagenta, Blue);
					}
					break;
					}

					if (langPos >= 5)
						langPos = 1;
					else if (langPos <= 0)
						langPos = 4;

					if (needToExit == 1) {
						SetColor(LightGray);
						system("cls");
						break;
					}
				} while (1);
			}
			break;
			case 2:
			{
				SetColor(LightGray);
				cout << "\t\t\t\t";
				SetColor(LightMagenta, Blue);
				cout << "\t\t   " << endl;
				char BD_NAME[] = "other.cfg";
				char PATH[_MAX_PATH];
				strcpy(PATH, GlobalVar::PATHTOEXE);
				char *p = strstr(PATH, GlobalVar::GAMENAME);
				strcpy(p, BD_NAME);
				ifstream fin(PATH);
				char cfgLanguage[5];
				fin >> cfgLanguage;
				fin.close();

				SetColor(LightGray);
				cout << "\t\t\t\t";
				SetColor(LightMagenta, Blue);
				cout << "\t\t   ";
				gotoxy(41, 2);
				cin >> GlobalVar::STANDART_BACKGROUND >> GlobalVar::STANDART_TEXT;

				ofstream fout(PATH);
				fout << cfgLanguage << endl;
				fout << "MAX MAX" << endl;
				fout << GlobalVar::STANDART_BACKGROUND << " " << GlobalVar::STANDART_TEXT << endl;
				fout << GlobalVar::MUSIC_VOLUME << " " << GlobalVar::SOUND_VOLUME;

				fout.close();
			}
			break;
			case 3:
			{
				SetColor(LightGray);
				cout << "\t\t\t\t\t\t";
				SetColor(LightMagenta, Blue);
				cout << "\t\t   " << endl;
				char BD_NAME[] = "other.cfg";
				char PATH[_MAX_PATH];
				strcpy(PATH, GlobalVar::PATHTOEXE);
				char *p = strstr(PATH, GlobalVar::GAMENAME);
				strcpy(p, BD_NAME);
				ifstream fin(PATH);
				char cfgLanguage[5];
				fin >> cfgLanguage;
				fin.close();

				int musicInput;
				do {
					gotoxy(0, 2);
					SetColor(LightGray);
					cout << "\t\t\t\t\t\t";
					SetColor(LightMagenta, Blue);
					cout << "Input music volume " << endl;
					SetColor(LightGray);
					cout << "\t\t\t\t\t\t";
					SetColor(LightMagenta, Blue);
					cout << "      [0..255]     " << endl;
					SetColor(LightGray);
					cout << "\t\t\t\t\t\t";
					SetColor(LightMagenta, Blue);
					cout <<"                   " ;
					gotoxy(57, 4);
					cin >> musicInput;
				} while (!(musicInput >= 0 && musicInput <= 255));

				ofstream fout(PATH);
				GlobalVar::MUSIC_VOLUME = musicInput;
				fout << cfgLanguage << endl;
				fout << "MAX MAX" << endl;
				fout << GlobalVar::STANDART_BACKGROUND << " " << GlobalVar::STANDART_TEXT << endl;
				fout << GlobalVar::MUSIC_VOLUME << " " << GlobalVar::SOUND_VOLUME;

				fout.close();
			}
			break;
			case 4: 
			{
				SetColor(LightGray);
				cout << "\t\t\t\t\t\t\t\t";
				SetColor(LightMagenta, Blue);
				cout << "\t\t   " << endl;
				char BD_NAME[] = "other.cfg";
				char PATH[_MAX_PATH];
				strcpy(PATH, GlobalVar::PATHTOEXE);
				char *p = strstr(PATH, GlobalVar::GAMENAME);
				strcpy(p, BD_NAME);
				ifstream fin(PATH);
				char cfgLanguage[5];
				fin >> cfgLanguage;
				fin.close();

				int musicInput;
				do {
					gotoxy(0, 2);
					SetColor(LightGray);
					cout << "\t\t\t\t\t\t\t\t";
					SetColor(LightMagenta, Blue);
					cout << "Input sound volume " << endl;
					SetColor(LightGray);
					cout << "\t\t\t\t\t\t\t\t";
					SetColor(LightMagenta, Blue);
					cout << "      [0..255]     " << endl;
					SetColor(LightGray);
					cout << "\t\t\t\t\t\t\t\t";
					SetColor(LightMagenta, Blue);
					cout << "                   ";
					gotoxy(73, 4);
					cin >> musicInput;
				} while (!(musicInput >= 0 && musicInput <= 255));

				ofstream fout(PATH);
				GlobalVar::SOUND_VOLUME = musicInput;
				fout << cfgLanguage << endl;
				fout << "MAX MAX" << endl;
				fout << GlobalVar::STANDART_BACKGROUND << " " << GlobalVar::STANDART_TEXT << endl;
				fout << GlobalVar::MUSIC_VOLUME << " " << GlobalVar::SOUND_VOLUME;

				fout.close();
			}
			break;
			case 5:
			{
			REPEAT_HELP_FOR_VERY_SMART_TESTERS:
				gotoxy(0, 2);
				char PATH[_MAX_PATH];
				ifstream fin;

				strcpy(PATH, GlobalVar::GAMELOCALE);
				strcat(PATH, "config_menu.help");

				fin.open(PATH);
				if (!fin.is_open()) {
					cout << "Cant open: " << PATH << endl;
				}
				unsigned long long FILE_LENGTH = 0;
				for (FILE_LENGTH = 0; fin.peek() != EOF; FILE_LENGTH++) {
					fin.get();
				}
				fin.seekg(0);
				char *help = new char[FILE_LENGTH + 1];
				for (unsigned long long i = 0; fin.peek() != EOF; i++) {
					help[i] = fin.get();
				}
				help[FILE_LENGTH] = '\0';
				cout << endl << help << endl << endl;

				fin.close();
				delete[] help;
			}
			break;
			case 6:
				return 1;
			break;
			}
			break;
		case '?':
			goto REPEAT_HELP_FOR_VERY_SMART_TESTERS;
			break;
		default:

			break;
		}

		if (menuMainPos >= 7)
			menuMainPos = 1;
		else if (menuMainPos <= 0)
			menuMainPos = 6;
	} while (1);

	return menuMain;
}
