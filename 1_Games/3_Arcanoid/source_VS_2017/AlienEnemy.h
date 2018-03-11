#ifndef _Alien_ENEMY_H_
#define _Alien_ENEMY_H_

#include "BasicEnemy.h"

class AlienEnemy : public BasicEnemy{
	ullint turnCooldown, turnCurrCooldown;
public:
	AlienEnemy(screenScene *Output);
	~AlienEnemy();

	ClearReturn IsClear() const;

	void Turn();
	void Print();

	void DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score);
};

#endif