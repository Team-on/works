#include "precompiledHeaders.h"
#include "dungeonCell.h"


dungeonCell::dungeonCell(){
	basicSymbol = displaySymbol = ' ';
	isSolid = 0;
}

dungeonCell::dungeonCell(char BasicSymbol, outputStyle Color) {
	basicSymbol = displaySymbol = BasicSymbol;
	displayColor  = basicColor = Color;
	isSolid = 0;
}

dungeonCell::~dungeonCell(){

}

void dungeonCell::SetDisplaySymbol(char sym) {
	displaySymbol = sym;
}
void dungeonCell::SetBasicSymbol(char sym) {
	basicSymbol = displaySymbol = sym;
	displayColor = basicColor;
}

void dungeonCell::SetDisplayColor(outputStyle Color) {
	displayColor = Color;
}
void dungeonCell::SetBasicColor(outputStyle Color) {
	displayColor = basicColor = Color;
}

void dungeonCell::SetIsSolid(bool solid) {
	isSolid = solid;
}

char dungeonCell::GetDisplaySymbol() const {
	return displaySymbol;
}
char dungeonCell::GetBasicSymbol() const {
	return basicSymbol;
}
outputStyle dungeonCell::GetDisplayColor() const {
	return displayColor;
}
outputStyle dungeonCell::GetBasicColor() const {
	return basicColor;
}

bool dungeonCell::GetIsSolid() const {
	return isSolid;
}