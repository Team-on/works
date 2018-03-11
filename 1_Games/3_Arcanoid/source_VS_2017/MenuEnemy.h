#ifndef _MENU_ENEMY_H_
#define _MENU_ENEMY_H_

#include "BasicEnemy.h"

class MenuEnemy : public BasicEnemy {
public:
	MenuEnemy(screenScene *Output);
	~MenuEnemy();

	//enum ClearReturn{AllDestroyed = 0,SomethingLeft, MenuStaticFigures, MenuEndlessFall, MenuAlien, MenuClassic, ClearReturnEND};
	ClearReturn IsClear() const;

	void Turn();
	void Print();

	void SetFigure(char ** figure, uchar sizeX, uchar sizeY);
	void DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score);
};

#endif