#ifndef _MOVE_KING_H_
#define _MOVE_KING_H_

#include "moveType.h"

class moveKing : public moveType{
public:
	bool CanMove(COORD from, COORD to);
};

#endif