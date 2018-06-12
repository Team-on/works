#ifndef _GAME_H_
#define _GAME_H_

#include "tetrisFigure.h"
#include "Button.h"

class Game{
	//Print info
	POINT fieldStartPos;
	POINT fieldSize;
	POINT boxSize;
	char borderWidth;
	hgeQuad *backgroundBlock, *backgroundScene;
	hgeQuad *blackBlock;

	//Field
	hgeQuad **field;
	bool **fieldFilled;

	//Falling figure
	tetrisFigure *figure;
	tetrisFigure *nextFigure;

	//Buttons 
	const char buttonsSize;
	Button **buttons; //Button *buttons[];

	bool isRunning;

public:
	bool isPaused;

	Game();
	~Game();

	//----------------------------------------- Save/Load -----------------------------------------
	void Save();
	void Load();

	//----------------------------------------- Main loop -----------------------------------------
	void Init();
	bool CheckExit();
	bool Loop();

	void Reload();

	void CheckButtons();
private:
	void DestroyLines();

	bool IsLose();
	//----------------------------------------- Fall -----------------------------------------
	void Fall();
	bool CheckCollisionWithFloor();
	bool CheckCollisionLeft();
	bool CheckCollisionRight();

	POINT ScreenPosToArrPos(POINT pos);
	void PassFigureToArr();

public:
	//----------------------------------------- Input -----------------------------------------
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Rotate();
	bool CanRotate();

	//----------------------------------------- FOR OUTPUT -----------------------------------------
	POINT GetSize() { return fieldSize; }
	hgeQuad **GetField() { return field; }
	bool **GetPrintMask() { return fieldFilled; }
	tetrisFigure *GetFallingFigure() { return figure; }
	tetrisFigure *GetNextFigure() { return nextFigure; }
	hgeQuad * GetBlocksBackground() { return backgroundBlock; }
	hgeQuad * GetSceneBackground() { return backgroundScene; }
	hgeQuad* GetBlackBlock() { return blackBlock; }
	void RenderButtons();

private:
	//----------------------------------------- GENERATOR -----------------------------------------
	tetrisFigure *CreateNewFallFigure();

	hgeColor GetRandomNonBlackColor();

	hgeQuad _basicQuad;
	void InitBasicQuad();
	hgeQuad CreateBlock(hgeColor color, POINT start, POINT size);

	//------------------------------------- Other --------------------------------------------------
	template <typename T>
	void DeleteMtx(T **ptr, size_t size) {
		for (size_t i = 0; i < size; ++i)
			delete[] ptr[i];
		delete[] ptr;
	}

	friend class tetrisFigure;
	friend class GameInfo;
	friend void RenderGame();
};

#endif