#ifndef _MOVE_DIAGONAL_H_
#define _MOVE_DIAGONAL_H_

#include "moveType.h"

class moveDiagonal : public moveType {
public:
	bool CanMove(COORD from, COORD to);
};

#endif