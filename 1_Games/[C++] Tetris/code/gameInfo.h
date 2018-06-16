#ifndef _GAME_INFO_H_
#define _GAME_INFO_H_

#include "scoreNumber.h"

class GameInfo {
	unsigned long long int score;
	POINT scorePos;
	ScoreNumber *scoreNumber;
	bool backPrinted;
	hgeQuad background;
public:
	GameInfo();
	~GameInfo();

	unsigned long long int GetScore() { return score; }
	void AddScore(int toAdd) { score += toAdd; }
	void PrintScore();

	void PrintBackGround();

	void Reload();
};

#endif