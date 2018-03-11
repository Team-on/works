#ifndef _ENDLESS_ENEMY_H_
#define _ENDLESS_ENEMY_H_

#include "BasicEnemy.h"

class EndlessEnemy : public BasicEnemy{
	ullint turnCooldown, turnCurrCooldown;
	uchar blockChanse, blockChanseUp, blockChanseUpMax;
public:
	EndlessEnemy(screenScene *Output);
	~EndlessEnemy();

	ClearReturn IsClear() const;

	void Turn();
	void Print();

	void DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score);
};

#endif