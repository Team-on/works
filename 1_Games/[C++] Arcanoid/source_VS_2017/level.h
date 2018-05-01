#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <algorithm>

#include "screenScene.h"

#include "Player.h"
#include "Bullet.h"

#include "BasicEnemy.h"
#include "StaticEnemy.h"

#include "ScoreKeeper.h"

class level{
	Player *player;
	vector <Bullet *> bullets;
	BasicEnemy *enemy;
	screenScene *output;
	ScoreKeeper *score;
public:
	level(Player * Player, BasicEnemy *Enemy, screenScene *Output, ScoreKeeper *Score);
	~level();

	void AddBullet(Bullet * bull);
	void MoveBullets();
	void PrintBullets();
	void PrintEnemy();
	void CalcBullets();

	void EnemyTurn();

	enum WinReturn{Win_None, Win_Win, Win_Lose, Win_MenuStaticFigures, Win_MenuEndlessFall, Win_MenuAlien, Win_MenuClassic};
	WinReturn IsWin();
};

#endif