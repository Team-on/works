#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

class _gameTime{
	const usint TicsInSecond;

	ullint ticTimer, ticTimerStep, ticTimerMax;
	usint gametimeTics;
	ullint gametime;
public:
	_gameTime();
	~_gameTime();

	ullint Tic();

	void SetTicTimerStep(ullint step);
	void SetTicTimerMax(ullint max);
};

#endif