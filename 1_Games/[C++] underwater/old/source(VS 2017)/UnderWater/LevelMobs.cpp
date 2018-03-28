#include "LevelMobs.h"



LevelMobs::LevelMobs(){
	lvlCurrent = 1;
	progressBar.ChangeBar(Yellow, LightGray, Black, ' ', 5);
	progressBar.SetRegen(0);
	progressBar.ChangeCurrent(0);
	progressBar.ChangeMax(XP_TABLE[1]);
}

LevelMobs::LevelMobs(int xpModNew) : LevelMobs(){
	xpMod = xpModNew;
}


LevelMobs::~LevelMobs(){
}

bool LevelMobs::IsNewLvl() const {
	if (xpCurrent >= xpToNextLevel)
		return 1;
	return 0;
}

void LevelMobs::GetXP(int get) {
	if (xpCurrent < xpToNextLevel) {
		if (get > 0) {
			get = get / 100 * (100 - xpMod);
			xpCurrent += get;
		if (xpCurrent > xpToNextLevel)
			xpCurrent = xpToNextLevel;
		}
		progressBar.ChangeCurrent(xpCurrent);
	}
}
bool LevelMobs::TryLvlUp() {
	if (IsNewLvl() && lvlCurrent != lvlMax) {
		progressBar.ChangeCurrent(0);
		progressBar.ChangeMax(XP_TABLE[lvlCurrent + 1]);
		lvlCurrent++;
		return 1;
	}
	return 0;
}

void LevelMobs::DrawBar() {
	if (IsNewLvl()) {
		progressBar.ChangeBar(Red, LightGray, Black, ' ', 5);
		progressBar.DrawBar();
		progressBar.ChangeBar(Yellow, LightGray, Black, ' ', 5);
	}
	else {
		progressBar.DrawBar();
	}
}

int LevelMobs::GetCurrLvl() {
	return lvlCurrent;
}

