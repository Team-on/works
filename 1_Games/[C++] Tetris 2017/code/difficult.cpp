#include "preCompiled.h"
#include "difficult.h"


Difficult::Difficult(float _reactionTimeGame, float _reactionStep, float _minReaction, char _scoreToSpeedUp) :
	reactionStep(_reactionStep),
	minReaction(_minReaction),
	scoreToSpeedUp(_scoreToSpeedUp),
	lastScore(_scoreToSpeedUp),
	_basicReaction(_reactionTimeGame)
{
	Reload();
}


Difficult::~Difficult(){
}

void Difficult::TrySpeedUp(unsigned long long int currentScore) {
	if (currentScore > lastScore + scoreToSpeedUp) {
		this->StepReaction();
		lastScore = currentScore;
		soundSound->Play("sounds\\LevelUp.ogg");
	}
}

void Difficult::Reload() {
	lastScore = scoreToSpeedUp;
	lastTimer = lastTimerNonGame = hge->Timer_GetTime();
	reactionTimeGame = _basicReaction;
}