#include "precompiledHeaders.h"
#include "figureTower.h"

figureTower::figureTower() {
	_moveType = new moveType*[2];
	_moveType[0] = new moveHorisontal;
	_moveType[1] = new moveVertical;

	this->style.SetSymbol('T');
}

figureTower::~figureTower() {
	for (uchar i = 0; i < 2; ++i)
		delete _moveType[i];
	delete[] _moveType;
}


int figureTower::IsValidTurn(COORD Pos) {
	for (uchar i = 0; i < 2; ++i) 
		if (_moveType[i]->CanMove(pos, Pos))
			return TURN::moveNKill;
	return TURN::cantMove;
}