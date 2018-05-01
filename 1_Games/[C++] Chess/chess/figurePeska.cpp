#include "precompiledHeaders.h"
#include "figurePeska.h"


figurePeska::figurePeska(){
	isWhite = 1;
	startPos.X = -20;
	this->style.SetSymbol('P');
}


figurePeska::~figurePeska(){
}

bool figurePeska::GetIsFirstTurn() const {
	return startPos == pos;
}

void figurePeska::SetIsWhite(bool IsWhite) {
	isWhite = IsWhite;
}

void figurePeska::SetPos(COORD newPos) {
	if(startPos.X == -20)
		startPos = newPos;
	pos = newPos;
}

int figurePeska::IsValidTurn(COORD Pos) {
	if (GetIsFirstTurn() && Pos.X == pos.X && Pos.Y == pos.Y - (isWhite ? 2 : -2)) 
		return TURN::moveOnly;
	

	if (abs(Pos.X - pos.X) == 1 && Pos.Y == pos.Y + (isWhite? -1 : 1)) 
		return TURN::killOnly;
	
	if (abs(Pos.X - pos.X) == 1 && Pos.Y == pos.Y + (isWhite ? -1 : 1)) 
		return TURN::killOnly;
	

	if (Pos.X == pos.X && Pos.Y == pos.Y - (isWhite ? 1 : -1)) 
		return TURN::moveOnly;
	
	
	return TURN::cantMove;
}

