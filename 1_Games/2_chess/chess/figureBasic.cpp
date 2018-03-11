#include "precompiledHeaders.h"
#include "figureBasic.h"


figureBasic::figureBasic(){
	isAlive = 1;
}


figureBasic::~figureBasic(){

}

bool figureBasic::GetIsAlive() {
	return isAlive;
}
char figureBasic::GetSymbol() {
	return style.GetSymbol();
}
COORD figureBasic::GetPos() const {
	return pos;
}

void figureBasic::SetIsAlive(bool IsAlive) {
	isAlive = IsAlive;
}
void figureBasic::SetSymbol(char sym) {
	style.SetSymbol(sym);
}
void figureBasic::SetPos(COORD newPos) {
	pos = newPos;
}


