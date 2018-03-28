#pragma once
#include "Stat.h"
#include "Race.h"
#include "Bar.h"
#include "LevelMobs.h"
#include "MobClass.h"

class Mob {
private:
	char *name;
	char symbol;

	LevelMobs lvl;

	Race race;
	MobClass Class;

	Stat strength;
	Stat agility;
	Stat endurance;
	Stat energy;
	Stat willpower;
	Stat charisma;
	Stat luck;

	Bar hp;
	Bar stamina;
	Bar mana;

public:
	Mob();
	Mob(char * Name, char Symbol, MobClass classs, Race racee);
	~Mob();

	void SetName(char *newName);
	void SetSymbol(char newS);


	void PlayerSave();
	void PlayerLoad();
	void PlayerPrintStats();
};

