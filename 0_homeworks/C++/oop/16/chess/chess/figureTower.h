#ifndef _FIGURA_TOWER_H_
#define _FIGURA_TOWER_H_

#include "figureBasic.h"

#include "moveType.h"
#include "moveVertical.h"
#include "moveHorisontal.h"

class figureTower : public figureBasic{
	moveType **_moveType;
public:
	figureTower();
	~figureTower();

	int IsValidTurn(COORD Pos);
};

#endif