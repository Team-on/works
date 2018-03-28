#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bullet.h"
#include "screenScene.h"

// 0
//123

class Player{
	COORD pos;
	screenObj sprite[4];
	screenScene *output;
public:
	Player(screenScene *outputScene);
	~Player();

	void SetSprite(const screenObj *spr);

	COORD GetPos() { return pos; }

	void Print() const;
	Bullet* Shot() const;
	void Move(COORD newPos);
};

#endif