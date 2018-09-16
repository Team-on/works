#include "stdafx.h"
#include "Game.h"
#include <ctime>
#include <random>



Game::Game() :
	map(new GameCell*[3]),
	isXFirst(true),
	botType(Medium)
{
	for(char i = 0; i < 3; ++i)
		map[i] = new GameCell[3];
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

	Winner w = CheckWinner();
	if(w != Winner::GameContinue){
		if(map[0][0].isActive)
			RevertActive();
		if(w == Winner::XWin){

		}
		else if(w == Winner::YWin){

		}
		else /*if(w == Winner::NoneWin)*/{

		}
	}
	else if(botType != Player)
		BotTurn();

	return true;
}

Game::Winner Game::CheckWinner(){
	char streaks[8];

	for(char type = GameCell::CellState::X; type <= GameCell::CellState::O; type++){
		memset(streaks, 0, sizeof(streaks[0]) * sizeof(streaks));

		for(char i = 0; i < 3; ++i){
			if(map[i][0].GetCellState() == type)
				++streaks[0];
			if(map[i][1].GetCellState() == type)
				++streaks[1];
			if(map[i][2].GetCellState() == type)
				++streaks[2];

			if(map[0][i].GetCellState() == type)
				++streaks[3];
			if(map[1][i].GetCellState() == type)
				++streaks[4];
			if(map[2][i].GetCellState() == type)
				++streaks[5];

			if(map[i][i].GetCellState() == type)
				++streaks[6];
			if(map[2 - i][i].GetCellState() == type)
				++streaks[7];
		}

		for(char i = 0; i < sizeof(streaks[0]) * sizeof(streaks); ++i){
			if(streaks[i] == 3)
				return type == GameCell::CellState::X ? Winner::XWin : Winner::YWin;
		}
	}
	for(char i = 0; i < 3; ++i)
		for(char j = 0; j < 3; ++j)
			if(map[i][j].GetCellState() == GameCell::CellState::Empty)
				return Winner::GameContinue;
	return Winner::NoneWin;
}

bool Game::IsPlayerTurn(){
	return isXTurn;
}

void Game::BotTurn(){
	for(char i = 0; i < 3; ++i)
		for(char j = 0; j < 3; ++j)
			if(map[i][j].GetCellState() == GameCell::CellState::Empty){
				(this->*botFunc)();
				isXTurn = !isXTurn;
				return;
			}
}

void Game::BotTurnEazy(){
	char x, y;
	do{
		x = rand() % 3;
		y = rand() % 3;
	} while(map[x][y].GetCellState() != GameCell::CellState::Empty);
	map[x][y].Place0();
}

void Game::BotTurnMedium(){
}

void Game::BotTurnHard(){
}

void Game::RevertActive(){
	for(char i = 0; i < 3; ++i)
		for(char j = 0; j < 3; ++j)
			map[i][j].isActive = !map[i][j].isActive;
}
