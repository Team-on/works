#include "precompiledHeaders.h"
#include "figureHorse.h"


figureHorse::figureHorse() {
	_moveType = new moveHoorse;
	this->style.SetSymbol('H');
}

figureHorse::~figureHorse() {
	delete _moveType;
}


int figureHorse::IsValidTurn(COORD Pos) {
	if (_moveType->CanMove(pos, Pos))
		return TURN::moveNKill;
	return TURN::cantMove;
}