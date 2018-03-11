#include "Dungeon.h"



Dungeon::Dungeon(){
	sizeX = sizeY = 0;
	mobs  = nullptr;
	dungeon = nullptr;
	player = nullptr;
}


Dungeon::~Dungeon(){
	for (int i = 0; i < sizeY; i++)
		delete[] dungeon[i];
	delete[] dungeon;
	delete player;
}
