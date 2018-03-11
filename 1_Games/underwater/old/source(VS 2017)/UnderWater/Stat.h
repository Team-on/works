#pragma once
#include "Includes.h"

class Stat {
private:
	short int base;
	short int current;
public:
	Stat();

	short int GetBase() const;
	short int GetCurr() const;

	// base + ch
	//Change current on ch too
	void ChangeBase(short int ch);
	// current + ch
	void ChangeCurr(short int ch);

	void SetBase(short int ch);
	void SetCurr(short int ch);

	//current = base;
	void Recalc();

	void FileRead(ifstream fin);
	void FileWrite(ofstream fout) const;
};

