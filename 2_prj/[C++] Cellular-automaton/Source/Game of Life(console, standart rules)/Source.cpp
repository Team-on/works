#include <iostream>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;

extern HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
extern HANDLE hConsoleRead = GetStdHandle(STD_INPUT_HANDLE);

#define ESC 27
#define TAB 9
#define ENTER 13
#define SPACE 23

#define ARROW_ALL 224
#define ARROW_UP 72
#define ARROW_RIGHT 77
#define ARROW_DOWN 80
#define ARROW_LEFT 75

enum ConcoleColorCl {
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
void Pause() {
	system("pause");
}
void SetColor(ConcoleColorCl text = LightGray, ConcoleColorCl back = Black) {
	SetConsoleTextAttribute(hConsole, (WORD)((back << 4) | text));
}

#define usi unsigned short int
class GameOfLife {
	const char cellSymbolDie = '.';
	const char cellSymbolAlive = '0';
	ConcoleColorCl aliveColor = LightGray;
	ConcoleColorCl dieColor = DarkGray;

	const usi sizeX, sizeY;
	char **arr;
	int **nbCnt;


	void SUP_NullNeightborns() {
		for (int i = 0; i < sizeY - 0; ++i)
			for (int j = 0; j < sizeX - 0; ++j)
				nbCnt[i][j] = 0;
	}
	void SUP_DrawCell(usi posX = 0, usi posY = 0) const {
		for (int i = 1; i < sizeY - 1; ++i) {
			for (int j = 1; j < sizeX - 1; ++j) {
				if (arr[i][j] == cellSymbolAlive) {
					gotoxy(posX + j - 1, posY + i - 1);
					SetColor(aliveColor);
					cout << cellSymbolAlive;
				}
				else {
					gotoxy(posX + j - 1, posY + i - 1);
					SetColor(dieColor);
					cout << cellSymbolDie;
				}
			}
		}
	}
public:
	GameOfLife() : sizeX(0), sizeY(0) {
		arr = nullptr;
		nbCnt = nullptr;
	}
	GameOfLife(usi SizeX, usi SizeY) : sizeX(SizeX + 2), sizeY(SizeY + 2) {
		arr = new char*[sizeY];
		nbCnt = new int*[sizeY];
		for (int i = 0; i < sizeY; ++i) {
			arr[i] = new char[sizeX];
			nbCnt[i] = new int[sizeX];
			for (int j = 0; j < sizeX; ++j) {
				arr[i][j] = cellSymbolDie;
				nbCnt[i][j] = 0;
			}
		}
	}
	~GameOfLife() {
		if (arr != nullptr) {
			for (int i = 0; i < sizeY; ++i)
				if (arr[i] != nullptr)
					delete[] arr[i];
			delete[] arr;
		}
		if (nbCnt != nullptr) {
			for (int i = 0; i < sizeY; ++i)
				if (nbCnt[i] != nullptr)
					delete[] nbCnt[i];
			delete[] nbCnt;
		}
	}

	void START_DrawAll(usi posX = 0, usi posY = 0) const{
		for (int i = 1; i < sizeY - 1; ++i) {
			gotoxy(posX, posY + i - 1);
			for (int j = 1; j < sizeX - 1; ++j)
				if (arr[i][j] == cellSymbolDie) {
					SetColor(dieColor);
					cout << arr[i][j];
				}
				else {
					SetColor(aliveColor);
					cout << arr[i][j];
				}
		}
	}
	void START_SetPopulation(int persent){
		long long int cnt = (double((sizeX - 2) * (sizeY - 2))) / 100 * persent;

		while (cnt) {
			usi posX, posY;
			do {
				posX = rand() % (sizeX - 2) + 1;
				posY = rand() % (sizeY - 2) + 1;
			} while (arr[posY][posX] == cellSymbolAlive);
			arr[posY][posX] = cellSymbolAlive;
			--cnt;
		}
	}
	void RESTART_Clear() {
		SUP_NullNeightborns();
		for (int i = 0; i < sizeY; ++i)
			for (int j = 0; j < sizeX; ++j)
				arr[i][j] = cellSymbolDie;
	}
	
	void GAME_CalcNeightborns() {
		for (int i = 1; i < sizeY - 1; ++i)
			for (int j = 1; j < sizeX - 1; ++j) {
				nbCnt[i][j] = 0;
				for (int ii = i - 1; ii <= i + 1; ++ii)
					for (int jj = j - 1; jj <= j + 1; ++jj)
						if (arr[ii][jj] == cellSymbolAlive && !(i == ii && j == jj))
							++nbCnt[i][j];
			}
	}
	void GAME_CalcGeneration_Draw(usi posX = 0, usi posY = 0) {
		for (int i = 1; i < sizeY - 1; ++i) {
			for (int j = 1; j < sizeX - 1; ++j) {
				if (arr[i][j] == cellSymbolAlive) {
					if (nbCnt[i][j] < 2) {
						arr[i][j] = cellSymbolDie;
						gotoxy(posX + j - 1, posY + i - 1);
						SetColor(dieColor);
						cout << cellSymbolDie;
						nbCnt[i][j] = -1;
					}
					if (nbCnt[i][j] > 3) {
						arr[i][j] = cellSymbolDie;
						gotoxy(posX + j - 1, posY + i - 1);
						SetColor(dieColor);
						cout << cellSymbolDie;
						nbCnt[i][j] = -1;
					}
				}
				else {
					if (nbCnt[i][j] == 3) {
						arr[i][j] = cellSymbolAlive;
						gotoxy(posX + j - 1, posY + i - 1);
						SetColor(aliveColor);
						cout << cellSymbolAlive;
						nbCnt[i][j] = -1;
					}
				}
			}
		}
	}

	void DEBUG_DrawNeighborns(usi posX = 0, usi posY = 0) const {
		for (int i = 1; i < sizeY - 1; ++i) {
			gotoxy(posX, posY + i - 1);
			for (int j = 1; j < sizeX - 1; ++j)
				if (arr[i][j] == cellSymbolDie) {
					if (nbCnt[i][j] != 3) {
						SetColor(DarkGray);
						cout << nbCnt[i][j];
					}
					else {
						SetColor(Yellow);
						cout << nbCnt[i][j];
					}	
				}
				else{
					if (nbCnt[i][j] < 2) {
						SetColor(Blue);
						cout << nbCnt[i][j];
					}
					else if (nbCnt[i][j] > 3) {
						SetColor(Red);
						cout << nbCnt[i][j];
					}
					else if (nbCnt[i][j] == 2 || nbCnt[i][j] == 3) {
						SetColor(Green);
						cout << nbCnt[i][j];
					}
				}
		}
		SetColor();
	}

	void COMB_Calc_Print_Neightborns(usi posX = 0, usi posY = 0) {
		for (int i = 1; i < sizeY - 1; ++i)
			for (int j = 1; j < sizeX - 1; ++j) {
				int prev = nbCnt[i][j];
				nbCnt[i][j] = 0;
				for (int ii = i - 1; ii <= i + 1; ++ii)
					for (int jj = j - 1; jj <= j + 1; ++jj)
						if (arr[ii][jj] == cellSymbolAlive && !(i == ii && j == jj))
							++nbCnt[i][j];
				if (prev != nbCnt[i][j]) {
					gotoxy(posX + j - 1, posY + i - 1);
					if (arr[i][j] == cellSymbolDie) {
						if (nbCnt[i][j] != 3) {
							SetColor(DarkGray);
							cout << nbCnt[i][j];
						}
						else {
							SetColor(Yellow);
							cout << nbCnt[i][j];
						}
					}
					else {
						if (nbCnt[i][j] < 2) {
							SetColor(Blue);
							cout << nbCnt[i][j];
						}
						else if (nbCnt[i][j] > 3) {
							SetColor(Red);
							cout << nbCnt[i][j];
						}
						else if (nbCnt[i][j] == 2 || nbCnt[i][j] == 3) {
							SetColor(Green);
							cout << nbCnt[i][j];
						}
					}
				}
			}
	}

	friend void GetInput_AddCellOnClick(GameOfLife &game);
};
#undef usi

int main(int argc, char *argv[]) {
	//Init
	{
		SetConsoleTitleA("Game of life");
		system("color 07");

		MoveWindow(FindWindow(NULL, "Game of life"), 0, 0, 200, 200, TRUE);
		COORD maxWindow = GetLargestConsoleWindowSize(hConsole);
		SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 4, maxWindow.Y - 2 };
		SMALL_RECT minWindow = { 0, 0, 0, 0 };
		SetConsoleWindowInfo(hConsole, true, &minWindow);
		SetConsoleScreenBufferSize(hConsole, maxWindow);
		SetConsoleWindowInfo(hConsole, true, &srctWindow);

		maxWindow.Y -= 2;
		maxWindow.Y *= 10;
		maxWindow.X *= 2;
		SetConsoleScreenBufferSize(hConsole, maxWindow);
		SetConsoleWindowInfo(hConsole, true, &srctWindow);

		srand(time(NULL));
	}
	
	//Flags
	bool paused = 1;
	bool neightbornsPrint = 0;
	int sleepTime = 100;

	int input;
	char menuChose = 0;
	const char *menuPunct[] = {
		"Pause",
		"DrawNb",
		"Sleep",
		"One Step",
		"New",
		"Exit"
	};

	//70 55
	int sizeX = 40, sizeY = 55;
	gotoxy(10, 5);
	cout << "Field size:" << endl;
	gotoxy(10, 6);
	cout << "Size X [10 .. 70]: ";
	cin >> sizeX;
	gotoxy(10, 7);
	cout << "Size Y [10 .. 55]: ";
	cin >> sizeY;
	system("cls");
	if (sizeX < 10)
		sizeX = 10;
	if (sizeY < 10)
		sizeY = 10;
	
	GameOfLife game(sizeX, sizeY);

	game.START_SetPopulation(40);
	game.DEBUG_DrawNeighborns(8 + sizeX, 3);
	game.START_DrawAll(4, 3);

	//First output
	SetColor(White);
	for (int i = 0; i < sizeof(menuPunct) / sizeof(menuPunct[0]); ++i) {
		if (i != menuChose) {
			gotoxy(13 + sizeX + sizeX, 3 + i);
			cout << menuPunct[i];
		}
		else {
			SetColor(Yellow);
			gotoxy(13 + sizeX + sizeX, 3 + i);
			cout << menuPunct[i];
			SetColor(White);
		}
	}
	{
		gotoxy(21 + sizeX + sizeX, 5);
		SetColor(DarkGray);
		cout << '[';
		SetColor(White);
		cout << sleepTime;
		SetColor(DarkGray);
		cout << ']';

		gotoxy(21 + sizeX + sizeX, 4);
		SetColor(DarkGray);
		cout << '[';
		SetColor(White);
		cout << "Off";
		SetColor(DarkGray);
		cout << ']';

		gotoxy(21 + sizeX + sizeX, 3);
		SetColor(DarkGray);
		cout << '[';
		SetColor(White);
		cout << "On";
		SetColor(DarkGray);
		cout << ']';
	}
	{
		const char *menuHelp[] = {
			"[0 .. 1]",
			"die in the next generation(underpopulation)",
			"[2 .. 3]",
			"alive",
			"[3]",
			"born in the next generation",
			"[4 .. 8]",
			"die in the next generation(Overpopulation)",
			"[0 .. 8]",
			"already dead",
			"[Arrows], [ENTER]",
			"menu control",
			"[ESC]",
			"exit"
		};
		for (int i = 0; i < sizeof(menuHelp) / sizeof(menuHelp[0]); i+=2) {
			gotoxy(13 + sizeX + sizeX, sizeof(menuPunct) / sizeof(menuPunct[0]) + 5 + i);
			if (i == 0)
				SetColor(Blue);
			else if (i == 2)
				SetColor(Green);
			else if (i == 4)
				SetColor(Yellow);
			else if (i == 6)
				SetColor(Red);
			else if (i == 8)
				SetColor(DarkGray);
			else
				SetColor(White);
			cout << menuHelp[i];
			SetColor(White);
			cout << " - " << menuHelp[i + 1];
		}
		
	}

	while (1) {	
		if (_kbhit()) {	
			input = _getch();
			switch (input) {
			case ARROW_ALL:
				input = _getch();
				switch (input) {
				case ARROW_UP:
					--menuChose;
					break;
				case ARROW_DOWN:
					++menuChose;
				}
				if (menuChose < 0)
					menuChose = sizeof(menuPunct) / sizeof(menuPunct[0]) - 1;
				if (menuChose >= sizeof(menuPunct) / sizeof(menuPunct[0]))
					menuChose = 0;
				break;
			case ENTER:
				switch (menuChose) {
				case 0:
				{
					paused = !paused;
					if (!paused) {
						gotoxy(22 + sizeX + sizeX, 3);
						cout << "   ";
						gotoxy(22 + sizeX + sizeX, 3);
						SetColor(White);
						cout << "Off";
						gotoxy(25 + sizeX + sizeX, 3);
						SetColor(DarkGray);
						cout << ']';
					}
					else {
						gotoxy(22 + sizeX + sizeX, 3);
						cout << "    ";
						gotoxy(22 + sizeX + sizeX, 3);
						SetColor(White);
						cout << "On";
						SetColor(DarkGray);
						cout << ']';
					}
				}
				break;
				case 1:
				{
					neightbornsPrint = !neightbornsPrint;
					if (!neightbornsPrint) {
						gotoxy(22 + sizeX + sizeX, 4);
						cout << "   ";
						gotoxy(22 + sizeX + sizeX, 4);
						SetColor(White);
						cout << "Off";
						gotoxy(25 + sizeX + sizeX, 4);
						SetColor(DarkGray);
						cout << ']';
					}
					else {
						gotoxy(22 + sizeX + sizeX, 4);
						cout << "    ";
						gotoxy(22 + sizeX + sizeX, 4);
						SetColor(White);
						cout << "On";
						SetColor(DarkGray);
						cout << ']';
						game.GAME_CalcNeightborns();
						game.DEBUG_DrawNeighborns(8 + sizeX, 3);
					}
				}
				break;
				case 2:
				{
					int tmp = 0, temp;
					gotoxy(22 + sizeX + sizeX, 5);
					cout << "       ";
					gotoxy(22 + sizeX + sizeX, 5);
					SetColor(White);
					cin >> sleepTime;
					if (sleepTime) {
						temp = sleepTime;
						while (temp != 0) {
							temp /= 10;
							++tmp;
						}
						gotoxy(22 + tmp + sizeX + sizeX, 5);
						SetColor(DarkGray);
						cout << ']';
					}
					else {
						gotoxy(23 + sizeX + sizeX, 5);
						SetColor(DarkGray);
						cout << ']';
					}
				}
				break;
				case 3:
					if (paused)
						goto GOTO_ONE_STEP;
				break;
				case 4:
				{
					int percent;
					gotoxy(22 + sizeX + sizeX, 7);
					SetColor(White);
					cout << "Percent: ";
					cin >> percent;
					if (percent < 0)
						percent = 0;
					else if (percent > 100)
						percent = 100;

					paused = 1;
					gotoxy(21 + sizeX + sizeX, 3);
					SetColor(DarkGray);
					cout << '[';
					SetColor(White);
					cout << "On";
					SetColor(DarkGray);
					cout << ']';

					game.RESTART_Clear();
					game.START_SetPopulation(percent);
					game.GAME_CalcNeightborns();
					if(neightbornsPrint)
						game.DEBUG_DrawNeighborns(8 + sizeX, 3);
					game.START_DrawAll(4, 3);

					gotoxy(22 + sizeX + sizeX, 7);
					cout << "            ";
				}
				break;
				case sizeof(menuPunct) / sizeof(menuPunct[0]) - 1:
					return EXIT_SUCCESS;
				break;
				}
			break;
			case ESC:
				return EXIT_SUCCESS;
			break;
			}

			SetColor(White);
			for (int i = 0; i < sizeof(menuPunct) / sizeof(menuPunct[0]); ++i) {
				if (i != menuChose) {
					gotoxy(13 + sizeX + sizeX, 3 + i);
					cout << menuPunct[i];
				}
				else {
					SetColor(Yellow);
					gotoxy(13 + sizeX + sizeX, 3 + i);
					cout << menuPunct[i];
					SetColor(White);
				}
			}
		}

		if (paused) {
			Sleep(10);
			continue;
		}
GOTO_ONE_STEP:

		if (neightbornsPrint) {
			game.GAME_CalcGeneration_Draw(4, 3);
			game.COMB_Calc_Print_Neightborns(8 + sizeX, 3);
		}
		else {
			game.GAME_CalcNeightborns();
			game.GAME_CalcGeneration_Draw(4, 3);
		}

		if (sleepTime)
			Sleep(sleepTime);
	}

	return EXIT_SUCCESS;
}