#ifndef _FIGURE_KING_H_
#define _FIGURE_KING_H_

#include "figureBasic.h"

#include "moveType.h"
#include "moveKing.h"

class figureKing : public figureBasic {
	moveType *_moveType;
public:
	figureKing();
	~figureKing();

	int IsValidTurn(COORD Pos);
};

#endif