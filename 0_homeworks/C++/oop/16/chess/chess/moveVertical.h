#ifndef _MOVE_VERTICAL_H_
#define _MOVE_VERTICAL_H_

#include "moveType.h"

class moveVertical : public moveType {

public:
	bool CanMove(COORD from, COORD to);
};

#endif