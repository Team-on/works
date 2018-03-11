#ifndef _MOVE_HOORSE_H_
#define _MOVE_HOORSE_H_

#include "moveType.h"

class moveHoorse : public moveType {
public:
	bool CanMove(COORD from, COORD to);
};

#endif