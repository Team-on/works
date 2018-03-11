#ifndef _GAME_H_
#define _GAME_H_

#include "screenScene.h"
#include "input_my.h"

#include "ScoreKeeper.h"
#include "Player.h"
#include "Bullet.h"
#include "level.h"

class GAME{
	bool isRunning;
	bool mainMenuBack;
	bool isAutoShoot, isPause;

	screenScene output;
	input_my input;

	BasicEnemy::ClearReturn gameMode;
	level *currLevel;


	ScoreKeeper score;
	
	//[1 .. 6]
	uchar difficult;
	ullint turnsToNextLvl;
	ullint turnCnt;

	uchar currShipHead, currShipSide, currShipCenter;
	outputStyle::color currShipColor;
	const char shipHead[7] = "^&#$|!";
	const char shipSide[19] = "(){}[];;::/\\||!!$$";
	const char shipCenter[7] = "@#%$&_";
	sint shootCooldawn, shootCurrCooldawn, pauseBlink;
	Player player;
public:
	GAME(uchar screenSizex, uchar screenSizey);
	~GAME();

	//-------------------- Main Loop -------------------------

	void MainLoop();

	void DoPlayerTurn();

	void PrintCurrState();

	//---------------- Menu ------------------------------

	int MainMenu();

	bool GetIsRunning() const;
	bool GetMainMenuBack() const;
private:

	void ChangeTurnCnt();
	void RestartDifficult();
	void CheckWin();

	//-------------------- Input ---------------------------------------
	int GetInput();
	int WaitForInput();

	//-------------- Add output element -----------------------------------------
	void ScreenSceneInit();
	void PrintDifficult();
	void BlickPause();
	void ClearField();

	void WinWin();
	void Lose();

	void ChangeShip();

	void MenuLevelHelp();
	void MenuLevelHelpClear();
};

#endif // !_GAME_H_

