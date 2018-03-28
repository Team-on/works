#include "precompiledHeaders.h"
#include "figureOfficer.h"


figureOfficer::figureOfficer() {
	_moveType = new moveDiagonal;
	this->style.SetSymbol('O');
}

figureOfficer::~figureOfficer() {
	delete _moveType;
}


int figureOfficer::IsValidTurn(COORD Pos) {
	if (_moveType->CanMove(pos, Pos))
			return TURN::moveNKill;
	return TURN::cantMove;
}
