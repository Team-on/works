#ifndef _DIFFICULT_H_
#define _DIFFICULT_H_

class Difficult{
	const float _basicReaction;
	const float minReaction;
	const float reactionStep;
	const char scoreToSpeedUp;

	unsigned long long int lastScore;

	float lastTimer;
	float lastTimerNonGame;
	float reactionTimeGame;
public:
	Difficult(float _reactionTimeGame, float _reactionStep, float _minReaction, char _scoreToSpeedUp);
	~Difficult();

	float GetReaction() { return reactionTimeGame; }
	float GetLastTimer() { return lastTimer; }
	float GetLastTimerNonGame() { return lastTimerNonGame; }

	void StepReaction() { if (reactionTimeGame > minReaction) reactionTimeGame -= reactionStep; }
	void SetLastTimer(float timer) { lastTimer = timer; }
	void SetLastTimerNonGame(float timer) { lastTimerNonGame = timer; }

	void TrySpeedUp(unsigned long long int currentScore);

	void Reload();
};

#endif