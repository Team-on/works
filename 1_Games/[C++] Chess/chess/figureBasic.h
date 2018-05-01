#ifndef _FIGURE_BASIC_H_
#define _FIGURE_BASIC_H_

#include "screenObj.h"

class figureBasic{
protected:
	COORD pos;
	bool isAlive;
public:
	screenObj style;

	figureBasic();
	~figureBasic();

	bool GetIsAlive();
	char GetSymbol();
	COORD GetPos() const;

	void SetIsAlive(bool IsAlive);
	void SetSymbol(char sym);
	virtual void SetPos(COORD newPos);

	virtual int IsValidTurn(COORD Pos) = 0;

	enum TURN {
		cantMove,
		moveOnly,
		moveNKill,
		killOnly
	};
};

#endif