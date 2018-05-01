#ifndef _FIGURE_HORSE_H_
#define _FIGURE_HORSE_H_

#include "figureBasic.h"

#include "moveType.h"
#include "moveHoorse.h"

class figureHorse : public figureBasic{
	moveType *_moveType;
public:
	figureHorse();
	~figureHorse();

	int IsValidTurn(COORD Pos);
};

#endif