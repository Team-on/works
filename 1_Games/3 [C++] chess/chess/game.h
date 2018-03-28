#ifndef _GAME_H_
#define _GAME_H_

#include "screenScene.h"
#include "input_my.h"
#include "LOG.h"

#include "figureBasic.h"
#include "figurePeska.h"
#include "figureTower.h"
#include "figureHorse.h"
#include "figureOfficer.h"
#include "figureQueen.h"
#include "figureKing.h"

#include "KillerList.h"

#include "IniParser.h"

class game{
	uchar cellSize;
	COORD outputStartPos;
	screenScene output;

	string exePath;
	int turnCurr;
	IniParser turnKeeper;

	char *lastInput, lastInputPos, lastInputSize;
	input_my input;

	const uchar logSize;
	LOG_GAME gameLog;
	
	figureBasic **currPlayer;
	figureBasic **black, **white;

	enum WINNER {NOBODY, WHITE, BLACK};
public:
	game(uchar screenSizex, uchar screenSizey, char **argv);
	~game();

	bool MainLoop();

private:
	void PlaceChess();

	int WaitInput();
	short NoneGameInput(int in);
	void CheatCheck();
	void CheatSuicide();
	void CheatChag();
	void CheatMat();

	bool Move(figureBasic *fig);
	bool IsFigureBetwen(COORD a, COORD b);
	void Kill(figureBasic *fig);
	void ChangeCurrPlayer();
	bool IsAllyFigure(figureBasic *fig);

	//Треба для перевірки мата, шаха(мат + фігура яка може бити короля не можу бути побита)
	KillerList CanBeKilled(figureBasic *fig);
	bool IsChag();
	bool IsMat();
	void ChagOutput();
	void MatOutput();

	bool longCastling();
	bool shortCastling();

	WINNER CheckWinner();
	void RestartGame();

	figureBasic * FindFigByPos(COORD pos);
	COORD ClickPosToChessPos(COORD clickPos);

	void Print();
	void OutputAddFrame() const;
	void OutputAddLog();
	void OutputAddChess();

	string TurnKeeperGetFigureLetter(figureBasic *fig);
	string TurnKeeperGetPos(COORD pos);
};

#endif