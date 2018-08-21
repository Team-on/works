#pragma once
#include "GameCell.h"

class Game{
public:
	Game();
	~Game();

	void StartNewGame();
	bool MakeTurn(char x, char y);
private:
	GameCell **map;
	bool isXFirst, isXTurn;

};

