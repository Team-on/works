#ifndef _BULLET_H_
#define _BULLET_H_

#include "screenScene.h"

class Bullet{
public:
	enum DIRECTION { up, down, DESTROY };
private:
	screenScene *output;

	DIRECTION direction;
	screenObj sprite;
	COORD pos;
public:
	Bullet(screenScene *screen, DIRECTION dir, COORD startPos, screenObj spr);
	~Bullet();

	void SetUnused(bool unUsed);
	bool GetUnused() const;

	COORD GetPos() const { return pos; }


	void Move();
	void Destroy();
	void Print() const;
};

#endif