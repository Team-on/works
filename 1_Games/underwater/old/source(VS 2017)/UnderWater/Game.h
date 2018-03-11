#pragma once
#include "Includes.h"
#include "OutputFunc.h"

#include "Mob.h"
#include "Dungeon.h"

class Game{
public://TODO: Вернуть в private.
	Mob *player;
	enum RETURN_CODES{EXIT, PLAYER_NOT_CREATED, PLAYER_CREATED};
private:
	void DrawFrame() const;
	void DrawLineDown(int lenght, int posX, int posY) const;
	void DrawNewGameBackground() const;
public:
	Game();
	~Game();

	int NewGame();
};

