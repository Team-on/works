#include "Includes.h"
#include "Stat.h"


Stat::Stat() {
	base = current = 1;
}

short int Stat::GetBase() const {
	return base;
}
short int Stat::GetCurr() const {
	return current;
}

void Stat::SetBase(short int ch) {
	base = ch;
	if (base < 1)
		base = 1;
	SetCurr(base);
}
void Stat::SetCurr(short int ch) {
	current = ch;
	if (current < 1)
		current = 1;
}

void Stat::ChangeBase(short int ch) {
	base += ch;
	if (base < 1)
		base = 1;
	ChangeCurr(ch);
}
void Stat::ChangeCurr(short int ch) {
	current += ch;
	if (current < 1)
		current = 1;
}

void Stat::Recalc() {
	current = base;
}

void Stat::FileRead(ifstream fin) {
	fin >> base >> current;
}
void Stat::FileWrite(ofstream fout) const {
	fout << base << current;
}
