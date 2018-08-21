#include "stdafx.h"
#include "Game.h"



Game::Game() :
	map(new GameCell*[3]
){
	for(char i = 0; i < 3; ++i)
		map[i] = new GameCell[3];
}


Game::~Game(){
	for(char i = 0; i < 3; ++i)
		delete[] map[i];
	delete[] map;
	map = nullptr;
}

bool Game::MakeTurn(char x, char y){
	return false;
}
