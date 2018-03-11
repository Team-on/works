#include "precompiledHeaders.h"
#include "figureKing.h"


figureKing::figureKing() {
	_moveType = new moveKing;
	this->style.SetSymbol('K');
}

figureKing::~figureKing() {
	delete _moveType;
}


int figureKing::IsValidTurn(COORD Pos) {
	if (_moveType->CanMove(pos, Pos))
		return TURN::moveNKill;
	return TURN::cantMove;
}
