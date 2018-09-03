#pragma once
#include "GameCell.h"

class Game{
public:
	Game();
	~Game();
	
	void SetHButton(char x, char y, HWND hb) { map[x][y].hButton = hb; }
	void SetIsXFirst(bool isXFirst) { this->isXFirst = isXFirst; }

	void StartNewGame();

	bool MakeTurn(char x, char y);
	
private:
	GameCell **map;
	bool isXFirst, isXTurn;

	bool IsPlayerTurn();
	void BotTurn();
};

