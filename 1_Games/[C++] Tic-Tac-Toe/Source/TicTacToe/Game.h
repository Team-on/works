#pragma once
#include "GameCell.h"

class Game{
public:
	enum BotType : char {Eazy, Medium, Hard, Player};

	Game();
	~Game();
	
	void SetHButton(char x, char y, HWND hb) { map[x][y].hButton = hb; }
	void SetIsXFirst(bool isXFirst) { this->isXFirst = isXFirst; }
	void SetBotType(BotType botType) { this->botType = botType; }

	void StartNewGame();

	bool MakeTurn(char x, char y);
	
private:
	BotType botType;
	void (Game::*botFunc)(void);

	GameCell **map;
	bool isXFirst, isXTurn;

	bool IsPlayerTurn();
	void BotTurn();

	void BotTurnEazy();
	void BotTurnMedium();
	void BotTurnHard();
};

