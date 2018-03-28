#pragma once
#include "DungeonCell.h"
#include "DMob.h"

class Dungeon{
	//������ �� ���� ����
	DungeonCell **dungeon;
	int sizeX, sizeY;

	//��������� �� ��� ���� � ����
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

