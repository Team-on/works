#ifndef __MOB_BASIC_H_H
#define __MOB_BASIC_H_H

#include "outputStyle.h"

#include "mobStat.h"
#include "bar.h"

class _mobBasic{
protected:
	char symbol;
	outputStyle color;
	COORD pos;

	bar hp;
	bar mp;
	bar stamina;
public:
	// -------------- Stats --------------------------------------------------------
	mobStat lengthOfView;
	mobStat reaction;

	// --------------------------------------------------------

	_mobBasic();
	_mobBasic(COORD Pos, char sym);
	~_mobBasic();

	//------------------------- output -------------------------

	screenObj* GetHPBar(uchar length);
	screenObj* GetMPBar(uchar length);
	screenObj* GetStaminaBar(uchar length);

	void SetPos(COORD Pos);
	void SetSymbol(char sym);
	void SetColor(outputStyle Color);

	COORD GetPos() const;
	char GetSymbol() const;
	outputStyle GetColor() const;
	// --------------------------------------------------------
};

#endif // !__MOB_BASIC_H_H

