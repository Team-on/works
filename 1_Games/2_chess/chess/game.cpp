#include "precompiledHeaders.h"
#include "game.h"

void game::PlaceChess() {
	for (uchar i = 0; i < 8; ++i) {
	white[i] = new figurePeska;	
	black[i + 8] = new figurePeska;
	((figurePeska*)(black[i + 8]))->SetIsWhite(0);
	}

	white[8] = new figureTower;
	white[15] = new figureTower;
	black[0] = new figureTower;
	black[7] = new figureTower;

	white[9] = new figureHorse;
	white[14] = new figureHorse;
	black[1] = new figureHorse;
	black[6] = new figureHorse;

	white[10] = new figureOfficer;
	white[13] = new figureOfficer;
	black[2] = new figureOfficer;
	black[5] = new figureOfficer;

	white[11] = new figureQueen;
	black[3] = new figureQueen;

	white[12] = new figureKing;
	black[4] = new figureKing;

	for (char i = 0; i < 8; ++i) {
		black[i]->SetPos({ i, 0 });
		black[i + 8]->SetPos({ i, 1 });
		black[i]->style.SetStyle({ outputStyle::color::Yellow, outputStyle::color::Black });
		black[i + 8]->style.SetStyle({ outputStyle::color::Yellow, outputStyle::color::Black });


		white[i]->SetPos({ i, 6 });
		white[i + 8]->SetPos({ i, 7 });
		white[i]->style.SetStyle({ outputStyle::color::Green, outputStyle::color::Black });
		white[i + 8]->style.SetStyle({ outputStyle::color::Green, outputStyle::color::Black });
	}
}

game::game(uchar screenSizex, uchar screenSizey, char **argv) : output(screenSizex, screenSizey), logSize(100), gameLog(logSize){
	turnCurr = 1;
	string currKeeperPath = exePath = argv[0];

	{
		ifstream check;
		int currGame = -1;
		char tmp[20];
		do {
			check.close();
			++currGame;
			_itoa(currGame, tmp, 10);
			currKeeperPath.resize(currKeeperPath.find_last_of('\\') + 1);
			currKeeperPath += string("turnKeeper") + tmp + ".txt";
			check.open(currKeeperPath.c_str());
		} while (check.is_open());
		ofstream checkOut(currKeeperPath);
		checkOut << "\n[White player]\n\n[Black player]\n\n";
		checkOut.close();
	}

	turnKeeper.Open(currKeeperPath.c_str());

	lastInputPos = 0;
	lastInputSize = 16;
	lastInput = new char[lastInputSize];
	for (uchar i = 0; i < lastInputSize; ++i)
		lastInput[i] = 0;

	output.SetTitle("Chess");
	output.MaximizeWindow();
	output.ClearScr();

	outputStartPos = { 10, 2 };
	cellSize = 6;
	
	white = new figureBasic *[16];
	black = new figureBasic *[16];
	PlaceChess();
	currPlayer = white;
	gameLog.LogAdd("ESC - exit");
	gameLog.LogAdd("type [OOOr] - long castling");
	gameLog.LogAdd("type [OOr] - short castling");
	gameLog.LogAdd("White turn");

	OutputAddFrame();
	Print();
}

game::~game(){
	for (uchar i = 0; i < 16; ++i) {
		delete white[i];
		delete black[i];
	}
	delete[] white;
	delete[] black;
	delete[] lastInput;
	output.BeforeExit();
}

bool game::MainLoop() {
	Print();

	int in = WaitInput();
	NoneGameInput(in);
	CheatCheck();

	figureBasic *chosenFig = nullptr;
	if (in == FROM_LEFT_1ST_BUTTON_PRESSED) 
		chosenFig = FindFigByPos(ClickPosToChessPos(settings.GetClickPos()));
	
	if (chosenFig != nullptr) 
		if (IsAllyFigure(chosenFig)) 
			if (Move(chosenFig))
				ChangeCurrPlayer();

	WINNER winner = CheckWinner();
	if (winner != WINNER::NOBODY) {
		if (winner == WINNER::BLACK) 
			gameLog.LogAdd("Black player win");
		else 
			gameLog.LogAdd("White player win");
		RestartGame();
	}

	return 1;
}

bool game::Move(figureBasic *fig) {
	short centerCell = short(round(float(cellSize - 1) / 2));
	output[outputStartPos.Y + fig->GetPos().Y  * cellSize + centerCell - 1]
		[outputStartPos.X + fig->GetPos().X * cellSize + centerCell - 1].SetStyle({ outputStyle::color::Magenta, fig->style.GetStyle().GetBack() });
	output.Print();

	int in = WaitInput();

	if (in == FROM_LEFT_1ST_BUTTON_PRESSED) {
		COORD movePos = ClickPosToChessPos(settings.GetClickPos());

		//Для перевибору фігури
		figureBasic * figureOnPos = FindFigByPos(movePos);
		if (IsAllyFigure(figureOnPos)) {
			{
				output[outputStartPos.Y + fig->GetPos().Y  * cellSize + centerCell - 1]
					[outputStartPos.X + fig->GetPos().X * cellSize + centerCell - 1].SetStyle(fig->style.GetStyle());
				output[outputStartPos.Y + fig->GetPos().Y  * cellSize + centerCell - 1]
					[outputStartPos.X + fig->GetPos().X * cellSize + centerCell - 1].SetSymbol(fig->GetSymbol());
			}

			return Move(FindFigByPos(ClickPosToChessPos(settings.GetClickPos())));
		}

		int isValidTurn = fig->IsValidTurn(movePos);
		if (isValidTurn) {
			if(fig != white[9] && fig != white[14] && fig != black[1] && fig != black[6])
				if (IsFigureBetwen(fig->GetPos(), movePos))
					return 0;

			//Щоб замінити символи фігури на ' '
			output[outputStartPos.Y + fig->GetPos().Y  * cellSize + centerCell - 1]
				[outputStartPos.X + fig->GetPos().X * cellSize + centerCell - 1].SetStyle({});
			output[outputStartPos.Y + fig->GetPos().Y  * cellSize + centerCell - 1]
				[outputStartPos.X + fig->GetPos().X * cellSize + centerCell - 1].SetSymbol(' ');

			if (figureOnPos != nullptr && (isValidTurn == figureBasic::TURN::killOnly || isValidTurn == figureBasic::TURN::moveNKill)) {
				char tmp[20];
				_itoa(turnCurr, tmp, 10);
				string valueKeeper = TurnKeeperGetFigureLetter(fig);
				valueKeeper += TurnKeeperGetPos(fig->GetPos()) + " : ";
				valueKeeper += TurnKeeperGetPos(movePos);

				Kill(figureOnPos);
				fig->SetPos(movePos);

				if (IsChag()) {
					if (IsMat()) {
						MatOutput();
						valueKeeper += " X";
					}
					else {
						ChagOutput();
						valueKeeper += " +";
					}
				}

				turnKeeper.WriteString(currPlayer == black ? "Black player" : "White player", tmp, valueKeeper);
				return 1;
			}
			else if (figureOnPos == nullptr && (isValidTurn == figureBasic::TURN::moveNKill || isValidTurn == figureBasic::TURN::moveOnly)) {
				char tmp[20];
				_itoa(turnCurr, tmp, 10);
				string valueKeeper = TurnKeeperGetFigureLetter(fig);
				valueKeeper += TurnKeeperGetPos(fig->GetPos()) + " - ";
				valueKeeper += TurnKeeperGetPos(movePos);

				fig->SetPos(movePos);

				if (IsChag()) {
					if (IsMat()){
						MatOutput();
						valueKeeper += " X";
					}
					else {
						ChagOutput();
						valueKeeper += " +";
					}
				}

				turnKeeper.WriteString(currPlayer == black ? "Black player" : "White player", tmp, valueKeeper);
				return 1;
			}
			return 0;
		}
	}
	return 0;
}

bool game::IsFigureBetwen(COORD a, COORD b) {
	char figCnt = 0;
	bool TryKill = (FindFigByPos(a) != nullptr || FindFigByPos(b) != nullptr);

	do {
		for (uchar i = 0; i < 16; ++i) {
			if (white[i]->GetPos() == a)
				++figCnt;
			if (black[i]->GetPos() == a)
				++figCnt;
		}

		if (a.X < b.X)
			++a.X;
		else if(a.X > b.X)
			--a.X;
		if (a.Y < b.Y)
			++a.Y;
		else if (a.Y > b.Y)
			--a.Y;
	} while (a != b);

	if (figCnt == 0)
		return 0;

	if (figCnt == 1 && TryKill == 1)
		return 0;

	return 1;
}

void game::ChangeCurrPlayer() {
	if (currPlayer == white) {
		gameLog.LogAdd("Black turn");
		currPlayer = black;
	}
	else {
		gameLog.LogAdd("White turn");
		currPlayer = white;
		++turnCurr;
	}
}

void game::Kill(figureBasic *fig) {
	fig->SetIsAlive(0);
	fig->SetPos({ -1, -1 });
}

bool game::IsAllyFigure(figureBasic *fig) {
	for (uchar i = 0; i < 16; ++i)
		if (currPlayer[i] == fig)
			return 1;
	return 0;
}

KillerList game::CanBeKilled(figureBasic *fig) {
	KillerList killers;
	figureBasic **enemyPlayer = nullptr;
	for (char i = 0; i < 16; ++i) {
		if (fig == black[i]) {
			enemyPlayer = white;
			break;
		}
		if (fig == white[i]) {
			enemyPlayer = black;
			break;
		}
	}
	
	for (char i = 0; i < 16; ++i)
		if (
			enemyPlayer[i]->GetIsAlive() &&
			(enemyPlayer[i]->IsValidTurn(fig->GetPos()) == figureBasic::TURN::moveNKill || enemyPlayer[i]->IsValidTurn(fig->GetPos()) == figureBasic::TURN::killOnly) &&
			(!IsFigureBetwen(enemyPlayer[i]->GetPos(), fig->GetPos()) || (enemyPlayer[i] == white[9] || enemyPlayer[i] == white[14] || enemyPlayer[i] == black[1] || enemyPlayer[i] == black[6]))
			)
			killers.AddKiller(enemyPlayer[i]);
	
	return killers;
}

bool game::IsChag() {
	return CanBeKilled((currPlayer == black) ? white[12] : black[4]).GetKillSize() != 0;
}

bool game::IsMat() {
	KillerList kingKillers = CanBeKilled(((currPlayer == black) ? white[12] : black[4]));
	char cnt = 0;
	
	for (char i = 0; i < kingKillers.GetKillSize(); ++i)
		if (CanBeKilled(kingKillers.GetKiller(i)).GetKillSize() == 0)
			++cnt;
	if(cnt != 0)
		return 1;

	for (char i = 0; i < 8; ++i) {
		KillerList killers;
		figureBasic **enemyPlayer = ((currPlayer == black) ? white : black);
		COORD newPos = (currPlayer == white) ? white[12]->GetPos() : black[4]->GetPos();
		figureBasic *alterKing = new figureKing;
		switch (i) {
		case 0:
			++newPos.X;
			break;
		case 1:
			--newPos.X;
			break;
		case 2:
			++newPos.Y;
			break;
		case 3:
			--newPos.Y;
			break;
		case 4:
			++newPos.X;
			++newPos.Y;
			break;
		case 5:
			--newPos.X;
			--newPos.Y;
			break;
		case 6:
			++newPos.X;
			--newPos.Y;
			break;
		case 7:
			++newPos.X;
			++newPos.Y;
			break;
		}
		if (newPos.X < 0 || newPos.X > 7 || newPos.Y < 0 || newPos.Y > 7) {
			delete alterKing;
			continue;
		}

		alterKing->SetPos(newPos);

		for (char i = 0; i < 16; ++i)
			if (
				enemyPlayer[i]->GetIsAlive() &&
				(enemyPlayer[i]->IsValidTurn(alterKing->GetPos()) == figureBasic::TURN::moveNKill || enemyPlayer[i]->IsValidTurn(alterKing->GetPos()) == figureBasic::TURN::killOnly) &&
				(!IsFigureBetwen(enemyPlayer[i]->GetPos(), alterKing->GetPos()) || (enemyPlayer[i] == white[9] || enemyPlayer[i] == white[14] || enemyPlayer[i] == black[1] || enemyPlayer[i] == black[6]))
				)
				killers.AddKiller(enemyPlayer[i]);
		if (killers.GetKillSize() != 0)
			return 1;
		delete alterKing;
	}
	return 0;
}

void game::ChagOutput() {
	string message = ((currPlayer == white) ? "White" : "Black");
	message += " have chag";
	gameLog.LogAdd(message);
}

void game::MatOutput() {
	gameLog.LogAdd(string(((currPlayer == white) ? "White" : "Black")) + " have MAT");
}

//Left
bool game::longCastling() {
	figureBasic *king, *tower;
	if (currPlayer == white) {
		king = white[12];
		tower = white[8];
	}
	else {
		king = black[4];
		tower = black[0];
	}
	if (!IsFigureBetwen(king->GetPos(), tower->GetPos())) {
		COORD tmp = king->GetPos();
		king->SetPos(tower->GetPos());
		tower->SetPos(tmp);
		return 1;
	}
	return 0;
}

//Right
bool game::shortCastling() {
	figureBasic *king, *tower;
	if (currPlayer == white) {
		king = white[12];
		tower = white[15];
	}
	else {
		king = black[4];
		tower = black[7];
	}
	if (!IsFigureBetwen(king->GetPos(), tower->GetPos())) {
		COORD tmp = king->GetPos();
		king->SetPos(tower->GetPos());
		tower->SetPos(tmp);
		return 1;
	}
	return 0;
}

COORD game::ClickPosToChessPos(COORD clickPos) {
	COORD rez = { 0 ,0 };

	rez.X = (float(clickPos.X - outputStartPos.X) / cellSize);
	rez.Y = (float(clickPos.Y - outputStartPos.Y) / cellSize);

	return rez;
}

figureBasic * game::FindFigByPos(COORD pos) {
	for (uchar i = 0; i < 16; ++i) {
		COORD currPos = black[i]->GetPos();
		if (currPos == pos && black[i]->GetIsAlive())
			return black[i];
		currPos = white[i]->GetPos();
		if (currPos == pos && white[i]->GetIsAlive())
			return white[i];
	}
	return nullptr;
}

int game::WaitInput() {
	int in = input.ReadInput();
	while (!INPUT_RIGHT(in)) {
		in = input.ReadInput();
		Sleep(1);
	}
	return in;
}

short game::NoneGameInput(int in) {
	switch (in) {
	case VK_ESCAPE:
		exit(EXIT_SUCCESS);
	break;
	}

	if (isalpha(in)) {
		lastInput[lastInputPos++] = in;
		if (lastInputPos == lastInputSize - 1) {
			for (uchar i = 0; i < lastInputSize; ++i) {
				lastInput[i] = lastInput[i + 1];
			}
			--lastInput;
		}
	}

	return 0;
}

//Рокировка тут же
void game::CheatCheck() {
	bool used = 0;
	if (strstr(lastInput, "suicide") != nullptr) {
		gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " cheat suicide");
		CheatSuicide();
		used = 1;
	}
	else if (strstr(lastInput, "mat") != nullptr) {
		gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " cheat mat");
		CheatMat();
		used = 1;
	}
	else if (strstr(lastInput, "chag") != nullptr) {
		gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " cheat chag");
		CheatChag();
		used = 1;
	}
	else if (strstr(lastInput, "OOOr") != nullptr) {
		if (longCastling()) {
			gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " do long castling");
			ChangeCurrPlayer();
		}
		else {
			gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " cant do long castling");
		}
		Print();
		used = 1;
	}
	else if (strstr(lastInput, "OOr") != nullptr) {
		if (shortCastling()) {
			gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " do short castling");
			ChangeCurrPlayer();
		}
		else {
			gameLog.LogAdd(string((currPlayer == white ? "white" : "black")) + " cant do short castling");
		}
		Print();
		used = 1;
	}

	//gameLog.LogAdd(lastInput);
	//Print();
	if (used) {
		for (char i = 0; i < lastInputSize; ++i)
			lastInput[i] = 0;
		lastInputPos = 0;
	}
}

void game::CheatSuicide() {
	short centerCell = short(round(float(cellSize - 1) / 2));
	for (char i = 0; i < 16; ++i) {
		output[outputStartPos.Y + currPlayer[i]->GetPos().Y  * cellSize + centerCell - 1]
			[outputStartPos.X + currPlayer[i]->GetPos().X * cellSize + centerCell - 1].SetStyle({});
		output[outputStartPos.Y + currPlayer[i]->GetPos().Y  * cellSize + centerCell - 1]
			[outputStartPos.X + currPlayer[i]->GetPos().X * cellSize + centerCell - 1].SetSymbol(' ');
		Kill(currPlayer[i]);
	}
}

void game::CheatChag() {
	currPlayer[(currPlayer == white) ? 10 : 2]->SetPos({ 5, 5 });
	((currPlayer == white) ? black[4] : white[12])->SetPos({ 4, 4 });
}

void game::CheatMat() {
	currPlayer[(currPlayer == white)?10:2]->SetPos({ 5, 5 });
	((currPlayer == white) ? black[4] : white[12])->SetPos({3, 3});
}

game::WINNER game::CheckWinner() {
	if (!white[12]->GetIsAlive())
		return WINNER::BLACK;
	if (!black[4]->GetIsAlive())
		return WINNER::WHITE;
	return WINNER::NOBODY;
}

void game::RestartGame() {
	gameLog.LogAdd("Game over. Press any key to restart");
	Print();
	WaitInput();
    /*
	for (uchar i = 0; i < 16; ++i) {
		delete white[i];
		delete black[i];
	}

	PlaceChess();
	currPlayer = white;
	gameLog.LogAdd(" ");
	gameLog.LogAdd("White turn");

	OutputAddFrame();
	Print();
	*/
	HWND hwnd;
	hwnd = FindWindow(NULL, exePath.c_str());
	ShellExecute(hwnd, "open", exePath.c_str(), NULL, NULL, SW_MAXIMIZE);
	exit(0);
}

void game::Print() {
	OutputAddChess();
	OutputAddLog();
	output.Print();
}

void game::OutputAddFrame() const {
	for (uchar i = 0; i < 8; ++i) {
		for (uchar j = 0; j < 8; ++j) {
			for (uchar ii = 0; ii < cellSize + 1; ++ii) {
				for (uchar jj = 0; jj < cellSize + 1; ++jj) {
					output[outputStartPos.Y + i * cellSize + ii - 1]
						[outputStartPos.X + j * cellSize + jj - 1].SetSymbol('#');
				}
			}
		}
	}
	for (uchar i = 0; i < 8; ++i) {
		for (uchar j = 0; j < 8; ++j) {
			for (uchar ii = 0; ii < cellSize; ++ii) {
				for (uchar jj = 0; jj < cellSize; ++jj) {
					output[outputStartPos.Y + i * cellSize + ii]
						[outputStartPos.X + j * cellSize + jj].SetSymbol('#');
				}
			}
		}
	}
	for (uchar i = 0; i < 8; ++i) {
		for (uchar j = 0; j < 8; ++j) {
			for (uchar ii = 0; ii < cellSize - 1; ++ii) {
				for (uchar jj = 0; jj < cellSize - 1; ++jj) {
					output[outputStartPos.Y + i * cellSize + ii]
						[outputStartPos.X + j * cellSize + jj].SetSymbol(' ');
					if(
						(j % 2 == i % 2) &&
						(ii == 0 || ii == cellSize - 2 || jj == 0 || jj == cellSize - 2)
						)
						output[outputStartPos.Y + i * cellSize + ii]
						[outputStartPos.X + j * cellSize + jj].SetStyle({outputStyle::color::Black, outputStyle::color::LightGray });
					else if (ii == 0 || ii == cellSize - 2 || jj == 0 || jj == cellSize - 2)
						output[outputStartPos.Y + i * cellSize + ii]
						[outputStartPos.X + j * cellSize + jj].SetStyle({ outputStyle::color::White, outputStyle::color::DarkGray });
					else
						output[outputStartPos.Y + i * cellSize + ii]
						[outputStartPos.X + j * cellSize + jj].SetStyle({ outputStyle::color::White, outputStyle::color::Black });
				}
			}
		}
	}
}

void game::OutputAddLog() {
	for (usint i = 0; i < 10; ++i) {
		string currLog = gameLog.LogGet(i);
		for (usint j = 0; j < currLog.length(); ++j) {
			output[outputStartPos.Y + i][outputStartPos.X + cellSize * 9 + j].SetSymbol(currLog[j]);
			if(i != 0)
				output[outputStartPos.Y + i][outputStartPos.X + cellSize * 9 + j].SetStyle({outputStyle::color::DarkGray, outputStyle::color::Black});
			else
				output[outputStartPos.Y + i][outputStartPos.X + cellSize * 9 + j].SetStyle({ outputStyle::color::White, outputStyle::color::Black });
		}
		for (usint j = currLog.length(); j < output.GetScreenSizex(); ++j) {
			output[outputStartPos.Y + i][outputStartPos.X + cellSize * 9 + j].SetSymbol(' ');
		}
	}
}

void game::OutputAddChess() {
	short centerCell = short(round(float(cellSize - 1) / 2));
	for (uchar i = 0; i < 16; ++i) {
		if (black[i]->GetIsAlive()) {
			output[outputStartPos.Y + black[i]->GetPos().Y * cellSize + centerCell - 1]
				[outputStartPos.X + black[i]->GetPos().X * cellSize + centerCell - 1].SetSymbol(black[i]->GetSymbol());
			output[outputStartPos.Y + black[i]->GetPos().Y  * cellSize + centerCell - 1]
				[outputStartPos.X + black[i]->GetPos().X * cellSize + centerCell - 1].SetStyle(black[i]->style.GetStyle());
		}

		if (white[i]->GetIsAlive()) {
			output[outputStartPos.Y + white[i]->GetPos().Y * cellSize + centerCell - 1]
				[outputStartPos.X + white[i]->GetPos().X * cellSize + centerCell - 1].SetSymbol(white[i]->GetSymbol());
			output[outputStartPos.Y + white[i]->GetPos().Y  * cellSize + centerCell - 1]
				[outputStartPos.X + white[i]->GetPos().X * cellSize + centerCell - 1].SetStyle(white[i]->style.GetStyle());

		}
	}
}

string game::TurnKeeperGetFigureLetter(figureBasic *fig) {
	string rez = "ERROR";
	if (currPlayer == black) {
		if (fig == black[8] || fig == black[9] || fig == black[10] || fig == black[11] || fig == black[12] || fig == black[13] || fig == black[14] || fig == black[15])
			rez = "";
		else if (fig == black[0] || fig == black[7])
			rez = "T";
		else if (fig == black[1] || fig == black[6])
			rez = "H";
		else if (fig == black[2] || fig == black[5])
			rez = "O";
		else if (fig == black[3])
			rez = "Q";
		else if (fig == black[4])
			rez = "K";
	}
	else {	
		if (fig == white[0] || fig == white[1] || fig == white[2] || fig == white[3] || fig == white[4] || fig == white[5] || fig == white[6] || fig == white[7])
			rez = "";
		else if (fig == white[8] || fig == white[15])
			rez = "T";
		else if (fig == white[9] || fig == white[14])
			rez = "H";
		else if (fig == white[10] || fig == white[13])
			rez = "O";
		else if (fig == white[11])
			rez = "Q";
		else if (fig == white[12])
			rez = "K";
	}
	return rez;
}

string game::TurnKeeperGetPos(COORD pos) {
	string rez;
	rez = char(pos.X + 'a');
	char tmp[20];
	_itoa(8 - pos.Y, tmp, 10);
	rez += tmp;
	return rez;
}
