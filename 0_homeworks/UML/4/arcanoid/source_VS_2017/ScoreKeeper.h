#ifndef _SCORE_KEEPER_H_
#define _SCORE_KEEPER_H_

#include "screenScene.h"

class ScoreKeeper{
	llint score;
	screenScene *output;
public:
	ScoreKeeper(screenScene *ptr);
	~ScoreKeeper();

	void Print();
	void Change(llint Score);
	void Set(llint Score);
};

#endif // !_SCORE_KEEPER_H_



