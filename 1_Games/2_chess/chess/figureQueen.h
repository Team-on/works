#ifndef _FIGURE_QUEEN_H_
#define _FIGURE_QUEEN_H_

#include "figureBasic.h"

#include "moveType.h"
#include "moveVertical.h"
#include "moveHorisontal.h"
#include "moveDiagonal.h"

class figureQueen :public figureBasic {
	moveType **_moveType;
public:
	figureQueen();
	~figureQueen();

	int IsValidTurn(COORD Pos);
};

#endif