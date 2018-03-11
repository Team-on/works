#ifndef _CLASSIC_ENEMY_H_
#define _CLASSIC_ENEMY_H_

#include "BasicEnemy.h"

class ClassicEnemy : public BasicEnemy{
public:
	ClassicEnemy(screenScene *Output);
	~ClassicEnemy();
};

#endif