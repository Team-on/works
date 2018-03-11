#ifndef _GAME_H_
#define _GAME_H_

#include "screenScene.h"
#include "input_my.h"

#include "gameTime.h"

#include "_room.h"

class GAME{
	bool isRunning;
	bool mainMenuBack;

	screenScene output;
	COORD camPos;
	COORD logStart, logEnd;
	input_my input;

	_gameTime gameTime;

	/*
	7 - ����, ������� - ����������(��������)

	̳���� ������� �� 3 ������:
	1 - 1, 2
	2 - 3, 4, 5
	3 - 6, 7

	��������� �� 7 ������, � ���� �� 7 �����, � � ������ ����� �� 7 ���
	� ������ �� 28 �����.
	�� �� 7(7.01 - ����), ���� �� 21(21.01 - ��)
	*/
	
	_mobBasic player;

	_room room;
public:
	GAME(uchar screenSizex, uchar screenSizey);
	~GAME();

	//-------------------- Main Loop -------------------------

	void MainLoop();

	void DoPlayerTurn();

	void PrintCurrState();

	void ObserverMode();

	//---------------- Menu ------------------------------

	int MainMenu();

	bool GetIsRunning() const;
	bool GetMainMenuBack() const;
private:
	//-------------------- Input ---------------------------------------
	int GetInput();
	int WaitForInput();

	//------------------- Menu -----------------------------------------

	void InitMenuFrame(COORD menuStart, COORD menuEnd);
	void InGameMenu();
	void SettingsMenu();

	//-------------- Add output element -----------------------------------------
	
	void OutputAddVisibleMap();
	void RecalcCamPos(COORD &startPos, COORD &endPos);
	bool LOVAlgoritm(COORD p1, COORD p2);
	void HightlightSymbol(dungeonMap &currMap, COORD mapPos, COORD outputPos);

	void OutputAddBars();

	void LogInit();
	void OutputAddLog();
};

#endif // !_GAME_H_

