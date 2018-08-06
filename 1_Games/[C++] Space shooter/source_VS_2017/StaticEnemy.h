#ifndef _STATIC_ENEMY_H_
#define _STATIC_ENEMY_H_
#include "BasicEnemy.h"

class StaticEnemy : public BasicEnemy{
	ullint turnCooldown, turnCurrCooldown;
public:
	StaticEnemy(screenScene *Output);
	~StaticEnemy();

	//enum ClearReturn{AllDestroyed = 0,SomethingLeft, MenuStaticFigures, MenuEndlessFall, MenuAlien, MenuClassic, ClearReturnEND};
	ClearReturn IsClear() const;

	void Turn();
	void Print();

	void SetFigure(char ** figure, uchar sizeX, uchar sizeY);
	void DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score);
};

#endif //_STATIC_ENEMY_H_