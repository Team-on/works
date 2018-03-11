#include "precompiledHeaders.h"
#include "figureQueen.h"


figureQueen::figureQueen() {
	_moveType = new moveType*[3];
	_moveType[0] = new moveHorisontal;
	_moveType[1] = new moveVertical;
	_moveType[2] = new moveDiagonal;

	this->style.SetSymbol('Q');
}

figureQueen::~figureQueen() {
	for (uchar i = 0; i < 3; ++i)
		delete _moveType[i];
	delete[] _moveType;
}


int figureQueen::IsValidTurn(COORD Pos) {
	for (uchar i = 0; i < 3; ++i)
		if (_moveType[i]->CanMove(pos, Pos))
			return TURN::moveNKill;
	return TURN::cantMove;
}
