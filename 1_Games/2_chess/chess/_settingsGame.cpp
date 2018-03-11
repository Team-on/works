#include "precompiledHeaders.h"
#include "_settingsGame.h"


_settingsGame::_settingsGame(){
	clickPos = { 0, 0 };
}


_settingsGame::~_settingsGame(){

}

void _settingsGame::SetClickPos(COORD pos) const {
	clickPos = pos;
}

COORD _settingsGame::GetClickPos() const {
	return clickPos;
}