#include "precompiledHeaders.h"
#include "outputStyle.h"


outputStyle::outputStyle() : fore(LightGray), back(Black) {

}

outputStyle::outputStyle(color Fore, color Back) : fore(Fore), back(Back) {

}

outputStyle::~outputStyle(){

}

void outputStyle::SetColor(const color Fore, const color Back) {
	fore = Fore;
	back = Back;
}

void outputStyle::SetConsoleColor() const {
	SetConsoleTextAttribute(HANDLE_OUTPUT, (WORD)((back << 4) | fore));
}

bool outputStyle::operator==(outputStyle rhs) const {
	return ((back == rhs.back) && (fore == rhs.fore));
}

bool outputStyle::operator!=(outputStyle rhs) const {
	return !(*this == rhs);
}