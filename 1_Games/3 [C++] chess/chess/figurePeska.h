#ifndef _FIGURE_PESKA_H_
#define _FIGURE_PESKA_H_

#include "figureBasic.h"

class figurePeska : public figureBasic{
	bool isWhite;
	COORD startPos;
public:
	figurePeska();
	~figurePeska();

	bool GetIsFirstTurn() const;

	void SetPos(COORD newPos);

	void SetIsWhite(bool IsWhite);

	int IsValidTurn(COORD Pos);
};


#endif