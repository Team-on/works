#include "precompiledHeaders.h"
#include "gameTime.h"


_gameTime::_gameTime() : TicsInSecond(5000){
	ticTimerMax = 32767;
	gametimeTics = gametime = ticTimerStep = ticTimer = 1;
}


_gameTime::~_gameTime(){ }

ullint _gameTime::Tic() {
	ullint prevTimer = ticTimer;

	ticTimer += ticTimerStep;

	if (ticTimer > ticTimerMax)
		ticTimer = ticTimerStep;

	gametimeTics += ticTimerStep;
	if (gametimeTics >= TicsInSecond) {
		gametime += gametimeTics / TicsInSecond;
		gametimeTics %= TicsInSecond;
	}

	return prevTimer;
}

void _gameTime::SetTicTimerStep(ullint step) {
	ticTimerStep = step;
}

void _gameTime::SetTicTimerMax(ullint max) {
	ticTimerMax = max;
}