#include "stdafx.h"
#include "Game.h"



Game::Game() :
	map(new GameCell*[3]
	){
	for(char i = 0; i < 3; ++i)
		map[i] = new GameCell[3];
	isXFirst = true;
	botType = Medium;
}


Game::~Game(){
	for(char i = 0; i < 3; ++i)
		delete[] map[i];
	delete[] map;
	map = nullptr;
}

void Game::StartNewGame(){
	for(char i = 0; i < 3; ++i)
		for(char j = 0; j < 3; ++j)
			map[i][j].Init();
	isXTurn = isXFirst;

	switch(botType){
	case Game::Eazy:
	botFunc = &Game::BotTurnEazy;
	break;
	case Game::Medium:
	botFunc = &Game::BotTurnMedium;
	break;
	case Game::Hard:
	botFunc = &Game::BotTurnHard;
	break;
	}

	if(!IsPlayerTurn())
		BotTurn();
}

bool Game::MakeTurn(char x, char y){
	if(!IsPlayerTurn() && botType != Player)
		return false;

	if(map[x][y].GetCellState() != GameCell::CellState::Empty)
		return false;

	if(isXTurn)
		map[x][y].PlaceX();
	else if(botType == Player)
		map[x][y].Place0();

	isXTurn = !isXTurn;

	if(botType != Player)
		BotTurn();

	return true;
}

bool Game::IsPlayerTurn(){
	return isXTurn;
}

void Game::BotTurn(){
	(this->*botFunc)();

	isXTurn = !isXTurn;
}

void Game::BotTurnEazy(){
}

void Game::BotTurnMedium(){
}

void Game::BotTurnHard(){
}
