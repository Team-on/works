#pragma once
#include "DungeonCell.h"
#include "DMob.h"

class Dungeon{
	//Массив на весь данж
	DungeonCell **dungeon;
	int sizeX, sizeY;

	//Указатели на всіх мобів в данжі
	DMob **mobs;
	DMob *player;
public:
	Dungeon();
	~Dungeon();

	void GetPlayer(Mob &playerNew) {
		player = new DMob;
		player->mob = &playerNew;
	}
};

