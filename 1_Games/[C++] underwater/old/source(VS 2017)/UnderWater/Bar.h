#pragma once
#include "OutputFunc.h"

class Bar{
private:
	int max;
	int current;
	int regenPerTurnBase;
	int regenPerTurnCurrent;

	//For Bar.Draw()
	ConsoleColor backgroundFull;
	ConsoleColor backgroundEmpty;
	ConsoleColor textColor;
	char symbol;
	double precision;
public:
	Bar();
	~Bar();

	// current +- add
	void ChangeCurrent(int add);
	// max +- add
	void ChangeMax(int add);
	// regenPerTurn +- add
	void ChangeRegenPerTurnBase(int add);
	// regenPerTurn +- add
	void ChangeRegenPerTurnCurrent(int add);

	void SetMax(int newMax);
	void SetCurrent(int newCurr);
	void SetRegen(int newRegen);

	int GetMax() const;
	int GetCurrent() const;
	int GetRegenPerTurnBase() const;
	int GetRegenPerTurnCurrent() const;

	void Regen();

	//regenPerTurnCurrent = regenPerTurnBase
	void Recalc();

	void DrawBar(ConsoleColor backgroundFull,
		ConsoleColor backgroundEmpty = (ConsoleColor)GlobalVar::STANDART_BACKGROUND,
		ConsoleColor text = (ConsoleColor)GlobalVar::STANDART_TEXT,
		char symbol = ' ',
		double precision = 2.8);

	//Set standrt values for this bar
	void ChangeBar(ConsoleColor backgroundFull,
		ConsoleColor backgroundEmpty = (ConsoleColor)GlobalVar::STANDART_BACKGROUND,
		ConsoleColor text = (ConsoleColor)GlobalVar::STANDART_TEXT,
		char symbol = ' ', 
		double precision = 2.8);
	//Use standrt values for this bar
	void DrawBar();
};

