#ifndef _MOVE_TYPE_H_
#define _MOVE_TYPE_H_

class moveType {

public:
	virtual bool CanMove(COORD from, COORD to) = 0;
};

#endif