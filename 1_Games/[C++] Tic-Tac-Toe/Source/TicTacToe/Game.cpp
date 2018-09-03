#include "stdafx.h"
#include "Game.h"



Game::Game() :
	map(new GameCell*[3]
	) {
	for (char i = 0; i < 3; ++i)
		map[i] = new GameCell[3];
	isXFirst = true;
}


Game::~Game() {
	for (char i = 0; i < 3; ++i)
		delete[] map[i];
	delete[] map;
	map = nullptr;
}

void Game::StartNewGame(){
	for (char i = 0; i < 3; ++i)
		for (char j = 0; j < 3; ++j)
			map[i][j].Init();
	isXTurn = isXFirst;
	if (!IsPlayerTurn())
		BotTurn();
}

bool Game::MakeTurn(char x, char y) {
	if (!IsPlayerTurn())
		return false;

	if(map[x][y].GetCellState() != GameCell::CellState::Empty)
		return false;

	map[x][y].PlaceX();
	BotTurn();

	return true;
}

bool Game::IsPlayerTurn(){
	return isXTurn;
}

void Game::BotTurn(){

}
