#include "Mob.h"
#include "Includes.h"

Mob::Mob() {
	name = nullptr;
	symbol = '@';

	strength.SetBase(10);
	agility.SetBase(10);
	endurance.SetBase(10);
	energy.SetBase(10);
	willpower.SetBase(10);
	charisma.SetBase(10);
	luck.SetBase(10);

	hp.ChangeBar(Red, LightGray, Black);
	stamina.ChangeBar(Green, LightGray, Black);
	mana.ChangeBar(Blue, LightGray, Black);
	hp.SetMax(100);
	hp.SetCurrent(100);
	stamina.SetMax(100);
	stamina.SetCurrent(100);
	mana.SetMax(100);
	mana.SetCurrent(100);
}
Mob::Mob(char * Name, char Symbol, MobClass classs, Race racee) : Mob::Mob() {
	SetName(Name);
	symbol = Symbol;
	Class = classs;
	race = racee;

	strength.SetBase(10);
	agility.SetBase(10);
	endurance.SetBase(10);
	energy.SetBase(10);
	willpower.SetBase(10);
	charisma.SetBase(10);
	luck.SetBase(10);

	hp.ChangeBar(Red, LightGray, Black);
	stamina.ChangeBar(Green, LightGray, Black);
	mana.ChangeBar(Blue, LightGray, Black);
	hp.SetMax(100);
	hp.SetCurrent(100);
	stamina.SetMax(100);
	stamina.SetCurrent(100);
	mana.SetMax(100);
	mana.SetCurrent(100);
}

Mob::~Mob() {
	if (name != nullptr)
		delete[] name;
}

void Mob::SetName(char *newName) {
	if (name != nullptr)
		delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}
void Mob::SetSymbol(char newS) {
	symbol = newS;
}

void Mob::PlayerPrintStats() {
	system("cls");
	cout << endl << symbol << ' ' << name << endl;
	
	{
		if (race.raceId == Race::MURLOC) 
			cout << "Murloc";
		else if (race.raceId == Race::MUTANT_MURLOC)
			cout << "Mutant murloc";
		else if (race.raceId == Race::MURGUL)
			cout << "Mur'gul";
		else if (race.raceId == Race::DEEP_SEA_MURLOC)
			cout << "Deep sea murloc";
		else if (race.raceId == Race::MURGHOUL)
			cout << "Mur'ghoul";
		else if (race.raceId == Race::GORLOC)
			cout << "Gorloc";
		else if (race.raceId == Race::JINUY)
			cout << "Jinyu";
	}

	cout << endl;
	cout << Class.GetName() << endl;
	cout << "STR:" << strength.GetCurr() << " (" << strength.GetBase() << ")" << endl;
	cout << "AGI:" << agility.GetCurr() << " (" << agility.GetBase() << ")" << endl;
	cout << "END:" << endurance.GetCurr() << " (" << endurance.GetBase() << ")" << endl;
	cout << "ENG:" << energy.GetCurr() << " (" << energy.GetBase() << ")" << endl;
	cout << "WILL:" << willpower.GetCurr() << " (" << willpower.GetBase() << ")" << endl;
	cout << "CHA:" << charisma.GetCurr() << " (" << charisma.GetBase() << ")" << endl;
	cout << "LUCK:" << luck.GetCurr() << " (" << luck.GetBase() << ")" << endl;

	cout << "LVL: " << lvl.GetCurrLvl() << ' ';      lvl.DrawBar();		cout << endl;
	hp.DrawBar();		cout << endl;
	stamina.DrawBar();	cout << endl;
	mana.DrawBar();		cout << endl;
}