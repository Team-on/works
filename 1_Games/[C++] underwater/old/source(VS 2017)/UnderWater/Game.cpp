#include "Game.h"

#define ESC 27
#define TAB 9
#define ENTER 13
#define SPACE 23
#define BACKSPACE 8

#define ARROW_ALL -32
#define ARROW_UP 72
#define ARROW_RIGHT 77
#define ARROW_DOWN 80
#define ARROW_LEFT 75

Game::Game(){
	player = nullptr;
}
Game::~Game(){
	if (player != nullptr)
		delete player;
}

void Game::DrawFrame() const {
	cout << "===============================================================================================================================================================" << endl;
	cout <<
		"|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n|                                                                                                                                                             |\n";
	cout << "===============================================================================================================================================================" << endl;
}
void Game::DrawLineDown(int lenght, int posX, int posY) const {
	for (int i = 0; i < lenght; i++) {
		gotoxy(posX, i + posY);
		cout << '|';
	}
}
void Game::DrawNewGameBackground() const {
	//With 160, height 54
	DrawFrame();
	DrawLineDown(46, 53, 9);
	DrawLineDown(46, 106, 9);
	gotoxy(0, 8);
	cout << "===============================================================================================================================================================";
	gotoxy(2, 2);
	cout << "Name: ";
	gotoxy(2, 4);
	cout << "Symbol: ";

	gotoxy(137, 2);
	cout << "###################";
	gotoxy(137, 3);
	cout << "#                 #";
	gotoxy(137, 4);
	cout << "#   Start Game    #";
	gotoxy(137, 5);
	cout << "#                 #";
	gotoxy(137, 6);
	cout << "###################";

	gotoxy(23, 9);
	cout << "Race:";
	gotoxy(76, 9);
	cout << "Class:";
	gotoxy(129, 9);
	cout << "Info:";
	gotoxy(107, 50);
	cout << "===================================================";
	gotoxy(108, 51);
	cout << char(24) << char(25) << char(26) << char(27) << " - керування";;
	gotoxy(108, 52);
	cout << "Раса впливає +- на багато що";
	gotoxy(108, 53);
	cout << "Класс використовується лише при створеннi i";
	gotoxy(108, 54);
	cout << " впливає на навики / початкові скіли";
}

int Game::NewGame() {
	//With 160, height 54
	DrawNewGameBackground();
	Race plRace;
	unsigned char migTimer = 0;
	const int raceCnt = 22,
		 classCnt = 3,
		columnCnt = 4;
	int currRacePos = 0,
		currClassPos = 0,
		//0 - Race, 1 - class, 2 - name, 3 -symbol, 4 - btn Start
		currColumn = 0;
	char currSym = '@',
		currName[30] = {0};
		strncpy(currName, getenv("UserName"), 29);

	char race[raceCnt][30] = {
	"Murloc",
	"Mutant murloc",
	"Mur'gul",
	"Deep sea murloc",
	"Mur'ghoul",
	"Gorloc",
	"Jinyu",
	"Наги",
	"Рокеи",
	"Акварии",
	"Мерроу",
	"Куо-тоа",
	"Савагины",
	"Скамы",
	"Локаты",
	"Седроны",
	"Номмо",
	"Пираниды",
	"Фентеки",
	"Гвильи",
	"Прилипалы",
	"Фентеки",
	};
	char classs[classCnt][30] = {
		"Warrior",
		"Mage",
		"Rogue",
	};

	while (1) {
		for (int i = 0; i < raceCnt; i++) {
			gotoxy(2, i + 10);
			if (i != currRacePos)
				cout << race[i];
			else {
				SetColor(Yellow);
				cout << race[i];
				SetColor();
			}
		}
		for (int i = 0; i < classCnt; i++) {
			gotoxy(55, i + 10);
			if (i != currClassPos)
				cout << classs[i];
			else {
				SetColor(Yellow);
				cout << classs[i];
				SetColor();
			}
		}
		
		gotoxy(8, 2);
		cout << currName;
		if (currColumn == 2) {
			gotoxy(8 + strlen(currName), 2);
			SetColor(Yellow);
			if (
				migTimer <= 31 ||
				(63 <= migTimer &&  migTimer <= 93) || 
				(124 <= migTimer &&  migTimer <= 155) ||
				(186 <= migTimer &&  migTimer <= 217)
				)
				cout << '_';
			//else
				cout << " ";
			++migTimer;
			SetColor();
		}

		gotoxy(10, 4);
		cout << currSym;
		if (currColumn == 3) {
			gotoxy(11, 4);
			SetColor(Yellow);
			if (
				migTimer <= 31 ||
				(63 <= migTimer &&  migTimer <= 93) ||
				(124 <= migTimer &&  migTimer <= 155) ||
				(186 <= migTimer &&  migTimer <= 217)
				)
				cout << '_';
			else
				cout << " ";
			++migTimer;
			SetColor();
		}

		//Вивод в info
		if (currColumn == 0) {
			plRace.ReadRaceBonus(currRacePos + 1);
			plRace.PrintRaceDetailsWithPreHistory(108, 10);
		}
		else if(currColumn == 1){
			if (currClassPos == 0) {
				gotoxy(108, 10);
				cout << "Воин";
			}
			else if (currClassPos == 1) {
				gotoxy(108, 10);
				cout << "Маг";
			}
			else if (currClassPos == 2) {
				gotoxy(108, 10);
				cout << "Вор";
			}
		}
		else if (currColumn == 2) {
			gotoxy(108, 10);
			cout << "Имя персонажа";
			gotoxy(109, 11);
			cout << "- Одне для всієї гри";
			gotoxy(109, 12);
			cout << "- Може містити будь-що";
			gotoxy(108, 14);
			cout << "[BACKSPACE] - стерти";
		}
		else if (currColumn == 3) {
			gotoxy(108, 10);
			cout << "Символ персонажа";
			gotoxy(109, 11);
			cout << "- Спробуйте [CRTL] + [a..z]";
		}
		else if (currColumn == 4) {
			gotoxy(108, 10);
			cout << "Змінити расу і клас більше не можна" << endl;
			gotoxy(108, 11);
			cout << "[ENTER] - Далі";
		}

		//Обработка ввода
		{
			char currBtn = 0, isHit = kbhit();
			if (currColumn == 2 || currColumn == 3) {
				if (isHit)
					currBtn = getch();
				else if (currColumn == 3)
					currBtn = currSym;
			}
			else
				currBtn = getch();
			switch (currBtn) {
			case ESC:
				return EXIT;
			case ARROW_ALL:
				currBtn = getch();
				switch (currBtn) {
				case ARROW_UP:
					if (currColumn == 0)
						--currRacePos;
					else if (currColumn == 1)
						--currClassPos;
					
				break;
				case ARROW_DOWN:
					if (currColumn == 0)
						++currRacePos;
					else if (currColumn == 1)
						++currClassPos;
				break;
				case ARROW_LEFT:
					if (currColumn == 2) {
						gotoxy(8 + strlen(currName), 2);
						cout << ' ';
					}
					else if (currColumn == 3) {
						gotoxy(11, 4);
						cout << ' ';
					}
					else if (currColumn == 4) {
						gotoxy(137, 2);
						cout << "###################";
						gotoxy(137, 3);
						cout << "#                 #";
						gotoxy(137, 4);
						cout << "#   Start Game    #";
						gotoxy(137, 5);
						cout << "#                 #";
						gotoxy(137, 6);
						cout << "###################";
					}
					--currColumn;
				break;
				case ARROW_RIGHT:
					if (currColumn == 2) {
						gotoxy(8 + strlen(currName), 2);
						cout << ' ';
					}
					else if (currColumn == 3) {
						gotoxy(11, 4);
						cout << ' ';
					}
					else if (currColumn == 4) {
						gotoxy(137, 2);
						cout << "###################";
						gotoxy(137, 3);
						cout << "#                 #";
						gotoxy(137, 4);
						cout << "#   Start Game    #";
						gotoxy(137, 5);
						cout << "#                 #";
						gotoxy(137, 6);
						cout << "###################";
					}
					++currColumn;
				break;
				}
				for (int i = 10; i < 50; i++) {
					gotoxy(108, i);
					cout << "                                                 ";
				}
			break;
			case BACKSPACE:
				if (currColumn == 2) 
					if(strlen(currName))
						currName[strlen(currName) - 1] = '\0';
			break;
			case ENTER:
				if (currColumn == 4) {
					MobClass plClass(MobClass::CLASS_TYPE(currClassPos), classs[currClassPos]);
					player = new Mob(currName, currSym, plClass, plRace);
					//player->SetName(currName);
					//player->SetSymbol(currSym);
					player->PlayerPrintStats();
					system("pause");
					return PLAYER_CREATED;
				}
			default:
				if (currColumn == 2 && currBtn != 0 && currBtn != ENTER) {
					char add[2] = { currBtn , '\0' };
					if(isHit && strlen(currName) <= 29)
						strcat(currName, add);
				}
				else if (currColumn == 3) {
					currSym = currBtn;
				}
			}
			if (currRacePos < 0)
				currRacePos = raceCnt - 1;
			else if (currRacePos >= raceCnt)
				currRacePos = 0;
			if (currClassPos < 0)
				currClassPos = classCnt - 1;
			else if (currClassPos >= classCnt)
				currClassPos = 0;
			if (currColumn < 0)
				currColumn = columnCnt;
			else if (currColumn > columnCnt)
				currColumn = 0;

			if (currColumn == 4) {
				SetColor(Yellow);
				gotoxy(137, 2);
				cout << "###################";
				gotoxy(137, 3);
				cout << "#                 #";
				gotoxy(137, 4);
				cout << "#   Start Game    #";
				gotoxy(137, 5);
				cout << "#                 #";
				gotoxy(137, 6);
				cout << "###################";
				SetColor();
			}
		}

	}
}

