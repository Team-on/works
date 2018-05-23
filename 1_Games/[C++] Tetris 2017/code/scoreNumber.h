#ifndef _SCORE_NUMBER_H_
#define _SCORE_NUMBER_H_

class ScoreNumber{
	hgeQuad n[10];
public:
	const short h = 298 / 7, w =  192 / 7;
	
	ScoreNumber();
	~ScoreNumber();

	void Init();

	void PrintNumber(POINT pos, int num);
};

#endif