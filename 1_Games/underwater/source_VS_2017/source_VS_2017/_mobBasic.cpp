#include "precompiledHeaders.h"
#include "_mobBasic.h"

#include "_room.h"

_mobBasic::_mobBasic(){
	pos.X = pos.Y = 0;
	symbol = '@';

	reaction.SetBase(-1);

	barHealth.SetMax(100);
	barHealth.SerCurr(40);
	barMana.SetMax(3);
	barMana.SerCurr(1);
	barStamina.SetMax(1000);
	barStamina.SerCurr(947);
}

_mobBasic::_mobBasic(COORD Pos, char sym) {
	pos = Pos;
	symbol = sym;
}

_mobBasic::~_mobBasic(){

}

screenObj* _mobBasic::GetHPBar(uchar length) {
	return barHealth.GetOutputBar(
		{outputStyle::color::Black, outputStyle::color::LightRed },
		{ outputStyle::color::Black , outputStyle::color::DarkGray },
		length
	);
}
screenObj* _mobBasic::GetMPBar(uchar length) {
	return barMana.GetOutputBar(
		{ outputStyle::color::Black, outputStyle::color::LightBlue },
		{ outputStyle::color::Black , outputStyle::color::DarkGray },
		length
	);
}
screenObj* _mobBasic::GetStaminaBar(uchar length) {
	return barStamina.GetOutputBar(
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
