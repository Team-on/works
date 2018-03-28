#include "Bar.h"



Bar::Bar(){
	max = current = 0;
	regenPerTurnCurrent = regenPerTurnBase = 0;
}
Bar::~Bar(){

}


void Bar::ChangeCurrent(int add) {
	current += add;
}
void Bar::ChangeMax(int add) {
	max += add;
	if (max < 1)
		max = 1;
	if (current > max)
		current = max;
}
void Bar::ChangeRegenPerTurnBase(int add) {
	regenPerTurnBase += add;
	regenPerTurnCurrent += add;
}
void Bar::ChangeRegenPerTurnCurrent(int add) {
	regenPerTurnCurrent += add;
}

void Bar::SetMax(int newMax) {
	max = newMax;
}
void Bar::SetRegen(int newRegen) {
	regenPerTurnBase = newRegen;
	Recalc();
}

int Bar::GetMax() const {
	return max;
}
int Bar::GetCurrent() const {
	return current;
}
int Bar::GetRegenPerTurnBase() const {
	return regenPerTurnBase;
}
int  Bar::GetRegenPerTurnCurrent() const {
	return regenPerTurnCurrent;
}

void  Bar::SetCurrent(int newCurr) {
	current = newCurr;
}

void Bar::Regen() {
	current += regenPerTurnCurrent;
	if (current < 1)
		current = 1;
	if (current > max)
		current = max;
}

void Bar::Recalc() {
	regenPerTurnCurrent = regenPerTurnBase;
}

void Bar::DrawBar(ConsoleColor backgroundFull, ConsoleColor backgroundEmpty, ConsoleColor textColor, char symbol, double precision)  {
	SetColor(textColor, backgroundFull);

	int currPersent = nearbyint ( double(current) / max * 100 / precision);

	for (int i = 0; i < currPersent; i++)
		cout << symbol;

	SetColor(textColor, backgroundEmpty);
	for (int i = currPersent; i < nearbyint (100. / precision); i++)
		cout << symbol;

	SetColor();
}

void Bar::ChangeBar(ConsoleColor NEWbackgroundFull, ConsoleColor NEWbackgroundEmpty, ConsoleColor NEWtextColor, char NEWsymbol, double NEWprecision) {
	backgroundFull = NEWbackgroundFull;
	backgroundEmpty = NEWbackgroundEmpty;
	textColor = NEWtextColor;
	symbol = NEWsymbol;
	precision = NEWprecision;
}


void Bar::DrawBar() {
	SetColor(textColor, backgroundFull);

	char numbered[50], tmp[50];
	int j = 0;
	itoa(current, numbered, 10);
	strcat(numbered, "/");
	itoa(max, tmp, 10);
	strcat(numbered, tmp);

	int currPersent = nearbyint(double(current) / max * 100 / precision);

	for (int i = 0; i < currPersent; i++) {
		if (nearbyint(100. / precision) / 100 * 40 < i && j < strlen(numbered)) {
			cout << numbered[j++];
		}
		else
			cout << symbol;
	}

	SetColor(textColor, backgroundEmpty);
	for (int i = currPersent; i < nearbyint(100. / precision); i++) {
		if (nearbyint(100. / precision) / 100 * 40 < i && j < strlen(numbered)) {
			cout << numbered[j++];
		}
		else
			cout << symbol;
	}

	SetColor();
}