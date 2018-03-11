#include "precompiledHeaders.h"
#include "_settingsGame.h"


_settingsGame::_settingsGame(){
	screenMoveType = fast;
	clickPos = { 0, 0 };
}


_settingsGame::~_settingsGame(){

}

void _settingsGame::SetScreenMoveType(SCREEN_MOVE_TYPE type) const {
	screenMoveType = type;
}
void _settingsGame::SetClickPos(COORD pos) const {
	clickPos = pos;
}

_settingsGame::SCREEN_MOVE_TYPE _settingsGame::GetScreenMoveType() const{
	return screenMoveType;
}
COORD _settingsGame::GetClickPos() const {
	return clickPos;
}