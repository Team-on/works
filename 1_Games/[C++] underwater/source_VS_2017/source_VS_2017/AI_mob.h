#ifndef _AI_MOB_H_
#define _AI_MOB_H_

#include "_mobBasic.h"

class AI_mob : public _mobBasic {
	//Коланди руху мають співпадати з напрямими руху в enum direction(globalVar.h)
	enum AI_COMMAND {
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_DOWN,
		MOVE_UP,
		NONE
	};
	enum BEHAVIOR_TYPE {
		
	};

	AI_COMMAND *strategy;

public:
	AI_mob();
	~AI_mob();

	bool AI_SeePlayer(_mobBasic &mob);

	bool AI_Move(_mobBasic &mob, AI_COMMAND moveDir);

	bool AI_MoveIfSeeWithoutWall(_mobBasic &mob);

	bool AI_DoTurn(_mobBasic &mob);
};

#endif // !_AI_MOB_H_
