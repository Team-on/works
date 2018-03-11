#include "DungeonCell.h"

DungeonCell::DungeonCell() {
	title = '#';
	light = isPassed = 0;
	currMob = nullptr;
}
DungeonCell::~DungeonCell() {}

