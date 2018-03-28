#pragma once
#include "Mob.h"

class DungeonCell {
private:
	char title;
	bool isPassed;
	int light;

	Mob * currMob;
public:
	DungeonCell();
	~DungeonCell();
};

