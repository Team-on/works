#pragma once
#include "OutputFunc.h"

class Race {
private:
	enum RACE { MURLOC = 1, MUTANT_MURLOC,  MURGUL, DEEP_SEA_MURLOC, MURGHOUL, GORLOC, JINUY};

	short int raceId;

	short int StrengthBonus;
	short int AgilityBonus;
	short int EnduranceBonus;
	short int EnergyBonus;
	short int WillpowerBonus;
	short int CharismaBonus;
	short int LuckBonus;

	short int HPBonusPerLevel;

	short int EXPPenalty;

public:
	Race();
	Race(Race& rhs);
	void ReadRaceBonus(int raceID);
	void PrintRaceDetailsWithPreHistory(int xStart, int yStart) const;

	RACE GetRaceId() const;

	friend class Mob;
	//friend void Mob::PlayerPrintStats();
};

