#pragma once
#include "Bar.h"

class LevelMobs{
private:
	int xpCurrent;
	int xpToNextLevel;
	int lvlCurrent;
	
	int xpMod;
	int lvlMax;
	int XP_TABLE[5] = { 0, 1000, 2125, 3350 };

	Bar progressBar;

	bool IsNewLvl() const;
public:
	LevelMobs();
	LevelMobs(int xpModNew);
	~LevelMobs();

	bool TryLvlUp();
	void DrawBar();
	void GetXP(int get);

	int GetCurrLvl();
};

