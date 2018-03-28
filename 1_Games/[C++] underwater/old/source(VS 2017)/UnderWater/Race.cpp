#include "Includes.h"
#include "Race.h"

Race::Race() {
	raceId =

		StrengthBonus =
		AgilityBonus =
		EnduranceBonus =
		EnergyBonus =
		WillpowerBonus =
		LuckBonus =

		HPBonusPerLevel =

		EXPPenalty = 0;
}
Race::Race(Race& rhs) {
	raceId = rhs.raceId;
	StrengthBonus = rhs.StrengthBonus;
	AgilityBonus = rhs.AgilityBonus;
	EnduranceBonus = rhs.EnduranceBonus;
	EnergyBonus = rhs.EnergyBonus;
	WillpowerBonus = rhs.WillpowerBonus;
	LuckBonus = rhs.LuckBonus;
	HPBonusPerLevel = rhs.HPBonusPerLevel;
	EXPPenalty = rhs.EXPPenalty;;
}

void Race::ReadRaceBonus(int raceID) {
	char BD_NAME[30] = "mobs\\";
	char PATH[_MAX_PATH];
	strcpy(PATH, GlobalVar::PATHTOEXE);
	char *p = strstr(PATH, GlobalVar::GAMENAME);
	ifstream fin;

	if (raceID == MURLOC)
		strcat(BD_NAME, "Murloc.race");
	else if (raceID == MUTANT_MURLOC)
		strcat(BD_NAME, "Mutant murloc.race");
	else if (raceID == MURGUL)
		strcat(BD_NAME, "Murgul.race");
	else if (raceID == DEEP_SEA_MURLOC)
		strcat(BD_NAME, "Deep sea murloc.race");
	else if (raceID == MURGHOUL)
		strcat(BD_NAME, "Mur\'ghoul.race");
	else if (raceID == GORLOC)
		strcat(BD_NAME, "Gorloc.race");
	else if (raceID == JINUY)
		strcat(BD_NAME, "Jinyu.race");

	strcpy(p, BD_NAME);

	fin.open(PATH);
	if (!fin.is_open()) {
		cout << "Cant open " << BD_NAME << endl;
	}
	
	fin >> raceId;
	//raceId = raceID;
	fin >> StrengthBonus >> AgilityBonus >> EnduranceBonus >> EnergyBonus >> WillpowerBonus >> LuckBonus >> CharismaBonus;
	fin >> HPBonusPerLevel;
	fin >> EXPPenalty;

	fin.close();
}

void Race::PrintRaceDetailsWithPreHistory(int xStart, int yStart) const{
	char BD_NAME[80];
	char PATH[_MAX_PATH];
	strcpy(PATH, GlobalVar::GAMELOCALE);
	ifstream fin;
	gotoxy(xStart, yStart);

	if (raceId == MURLOC) {
		cout << "Murloc:";
		strcpy(BD_NAME, "Murloc pre history.lang");
	}
	else if (raceId == MUTANT_MURLOC) {
		cout << "Mutant murloc:";
		strcpy(BD_NAME, "Mutant murloc pre history.lang");
	}
	else if (raceId == MURGUL){
		cout << "Mur'gul:";
		strcpy(BD_NAME, "Murgul pre history.lang");
	}
	else if (raceId == DEEP_SEA_MURLOC) {
		cout << "Deep sea murloc:";
		strcpy(BD_NAME, "Deep sea murloc pre history.lang");
	}
	else if (raceId == MURGHOUL) {
		cout << "Mur'ghoul:";
		strcpy(BD_NAME, "Mur\'ghoul pre history.lang");
	}
	else if (raceId == GORLOC) {
		cout << "Gorloc:";
		strcpy(BD_NAME, "Gorloc pre history.lang");
	}
	else if (raceId == JINUY) {
		cout << "Jinyu:";
		strcpy(BD_NAME, "Jinyu pre history.lang");
	}

	strcat(PATH, BD_NAME);
	fin.open(PATH);
	if (!fin.is_open()) {
		cout << "Cant open: " << PATH << endl;
	}
	unsigned long long FILE_LENGTH = 0;
	for (FILE_LENGTH = 0; fin.peek() != EOF; FILE_LENGTH++) {
		fin.get();
	}
	fin.seekg(0);
	char *preHistory = new char[FILE_LENGTH + 1];
	for (unsigned long long i = 0; fin.peek() != EOF; i++) {
		preHistory[i] = fin.get();
	}
	preHistory[FILE_LENGTH] = '\0';
	int currCoutPreHistoryPosY = yStart + 2;
	const int MAX_PRE_HISTORY_LINE_LENTH = 49;
	int currLinePos = 0;
	gotoxy(xStart, currCoutPreHistoryPosY);
	for (int i = 0; i < FILE_LENGTH; ++i) {
		if (preHistory[i] != '\n') {
			//ўоб не оставл€ти по 1-2 букви
			if ((currLinePos == MAX_PRE_HISTORY_LINE_LENTH - 1 || currLinePos == MAX_PRE_HISTORY_LINE_LENTH - 2) && preHistory[i - 1] == ' ' && preHistory[i] != ' ') {
				currLinePos = 0;
				gotoxy(xStart, ++currCoutPreHistoryPosY);
			}
			//ўоб оставити перенос 
			else if (currLinePos == MAX_PRE_HISTORY_LINE_LENTH - 1 && preHistory[i] != ' ' && preHistory[i - 1] != ' ') {
				cout << '-';
				currLinePos = 0;
				gotoxy(xStart, ++currCoutPreHistoryPosY);
			}
			//ўоб не вийти за меж≥
			else if (currLinePos == MAX_PRE_HISTORY_LINE_LENTH) {
				currLinePos = 0;
				gotoxy(xStart, ++currCoutPreHistoryPosY);
			}
			cout << preHistory[i];
			currLinePos++;
		}
		else {
			currLinePos = 0;
			gotoxy(xStart, ++currCoutPreHistoryPosY);
		}
	}
	
	fin.close();

	gotoxy(xStart, currCoutPreHistoryPosY += 2);
	cout << "Strengt: \t" << StrengthBonus;
	gotoxy(xStart, ++currCoutPreHistoryPosY);
	cout << "Agility: \t" << StrengthBonus ;
	gotoxy(xStart, ++currCoutPreHistoryPosY);
	cout << "Endurance: \t" << StrengthBonus;
	gotoxy(xStart, ++currCoutPreHistoryPosY);
	cout << "Energy: \t" << StrengthBonus;
	gotoxy(xStart, ++currCoutPreHistoryPosY);
	cout << "Charisma: \t" << CharismaBonus;
	gotoxy(xStart, ++currCoutPreHistoryPosY);
	cout << "Willpower: \t" << StrengthBonus;
	gotoxy(xStart, ++currCoutPreHistoryPosY);
	cout << "Luck: \t" << LuckBonus;
	gotoxy(xStart, currCoutPreHistoryPosY += 2);
	cout << "HP/LVL: \t" << HPBonusPerLevel;
	gotoxy(xStart, currCoutPreHistoryPosY += 2);
	cout << "EXP penalty: \t" << EXPPenalty;

	delete[] preHistory;
}

Race::RACE Race::GetRaceId() const {
	return Race::RACE(raceId);
}