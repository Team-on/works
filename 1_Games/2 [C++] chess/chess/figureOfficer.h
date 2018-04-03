#ifndef _FIGURE_OFFICER_H_
#define _FIGURE_OFFICER_H_

#include "figureBasic.h"

#include "moveType.h"
#include "moveDiagonal.h"

class figureOfficer : public figureBasic {
	moveType *_moveType; 
public:
	figureOfficer();
	~figureOfficer();

	int IsValidTurn(COORD Pos);
};

#endif