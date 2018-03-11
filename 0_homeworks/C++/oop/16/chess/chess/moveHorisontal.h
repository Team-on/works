#ifndef _MOVE_HORISONTAL_H_
#define _MOVE_HORISONTAL_H_

#include "moveType.h"

class moveHorisontal : public moveType{

public:
	bool CanMove(COORD from, COORD to);
};

#endif