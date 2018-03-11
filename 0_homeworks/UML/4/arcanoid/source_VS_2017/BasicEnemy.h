#ifndef _BASIC_ENEMY_H_
#define _BASIC_ENEMY_H_

#include <vector>
#include "Bullet.h"
#include "ScoreKeeper.h"
#include "screenScene.h"

class BasicEnemy{
protected:
	COORD leftUpCorner;
	uchar arrSizeY, arrSizeX;
	char ** arr;
	screenScene *output;
public:
	BasicEnemy();
	virtual ~BasicEnemy();

	void SetLeftUpCorner(COORD LeftUpCorner) { leftUpCorner = LeftUpCorner; }
	COORD GetLeftUpCorner() const { return leftUpCorner; }

	uchar LowestBlockPosY() const;

	enum ClearReturn{AllDestroyed = 0,SomethingLeft, MenuStaticFigures, MenuEndlessFall, MenuAlien, MenuClassic, MenuLevel, ClearReturnEND};
	virtual ClearReturn IsClear() const = 0;
	virtual void Turn() = 0;
	virtual void Print() = 0;

	virtual void DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score) = 0;

	static BasicEnemy * CreateEnemy(ClearReturn type, screenScene *output);
};

#endif //_BASIC_ENEMY_H_