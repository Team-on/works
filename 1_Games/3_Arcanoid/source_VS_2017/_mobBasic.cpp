#include "precompiledHeaders.h"
#include "_mobBasic.h"

#include "_room.h"

_mobBasic::_mobBasic(){
	pos.X = pos.Y = 0;
	symbol = '@';

	reaction.SetBase(-1);

	hp.SetMax(100);
	hp.SerCurr(40);
	mp.SetMax(3);
	mp.SerCurr(1);
	stamina.SetMax(1000);
	stamina.SerCurr(947);
}

_mobBasic::_mobBasic(COORD Pos, char sym) {
	pos = Pos;
	symbol = sym;
}

_mobBasic::~_mobBasic(){

}

screenObj* _mobBasic::GetHPBar(uchar length) {
	return hp.GetOutputBar(
		{outputStyle::color::Black, outputStyle::color::LightRed },
		{ outputStyle::color::Black , outputStyle::color::DarkGray },
		length
	);
}
screenObj* _mobBasic::GetMPBar(uchar length) {
	return mp.GetOutputBar(
		{ outputStyle::color::Black, outputStyle::color::LightBlue },
		{ outputStyle::color::Black , outputStyle::color::DarkGray },
		length
	);
}
screenObj* _mobBasic::GetStaminaBar(uchar length) {
	return stamina.GetOutputBar(
		{ outputStyle::color::Black, outputStyle::color::LightGreen },
		{ outputStyle::color::Black , outputStyle::color::DarkGray },
		length
	);
}

void _mobBasic::SetPos(COORD Pos) {
	pos = Pos;
}
void _mobBasic::SetSymbol(char sym) {
	symbol = sym;
}
void _mobBasic::SetColor(outputStyle Color) {
	color = Color;
}

COORD _mobBasic::GetPos() const {
	return pos;
}
char _mobBasic::GetSymbol() const {
	return symbol;
}
outputStyle _mobBasic::GetColor() const {
	return color;
}
