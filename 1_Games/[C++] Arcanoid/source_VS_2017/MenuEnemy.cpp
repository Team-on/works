#include "precompiledHeaders.h"
#include "MenuEnemy.h"


MenuEnemy::MenuEnemy(screenScene *Output) {
	output = Output;

	const uchar sizeX = 38, sizeY = 11;
	arrSizeY = sizeY;
	arrSizeX = sizeX;
	arr = new char*[sizeY];
#define $ '$'
		char mapTmp[sizeY][sizeX] = {
		//0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 23 24 25 26 27 28 29 30 31 32 33 34 35 36
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $ },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, 0, 0, $, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, $, 0, 0 },
		{ 0, 0, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, $, 0, $, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, 0, 0, $, 0, 0 },
		{ $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, 0 },
		{ 0, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, $, 0, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, 0, 0, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $ },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		};
#undef $
		for (uchar i = 0; i < sizeY; ++i) {
			arr[i] = new char[sizeX];
			for (uchar j = 0; j < sizeX; ++j)
				arr[i][j] = mapTmp[i][j];
		}
}

MenuEnemy::~MenuEnemy() {

}

//enum ClearReturn{AllDestroyed = 0,SomethingLeft, MenuStaticFigures, MenuEndlessFall, MenuAlien, MenuClassic, ClearReturnEND};
BasicEnemy::ClearReturn MenuEnemy::IsClear() const {
	bool currCheck = 1;
	for (uchar i = 0; i < arrSizeY; ++i) {
		for (uchar j = 0; j < 8; ++j) {
			if (arr[i][j] != 0)
				currCheck = 0;
		}
	}
	if (currCheck) 
		return MenuAlien;

	currCheck = 1;
	for (uchar i = 0; i < arrSizeY; ++i) {
		for (uchar j = 12; j < 17; ++j) {
			if (arr[i][j] != 0)
				currCheck = 0;
		}
	}
	if (currCheck)
		return MenuEndlessFall;

	currCheck = 1;
	for (uchar i = 0; i < arrSizeY; ++i) {
		for (uchar j = 22; j < 30; ++j) {
			if (arr[i][j] != 0)
				currCheck = 0;
		}
	}
	if (currCheck)
		return MenuClassic;

	currCheck = 1;
	for (uchar i = 0; i < arrSizeY; ++i) {
		for (uchar j = 32; j < 37; ++j) {
			if (arr[i][j] != 0)
				currCheck = 0;
		}
	}
	if (currCheck)
		return MenuStaticFigures;

	return SomethingLeft;
}

void MenuEnemy::Turn() {

}

void MenuEnemy::Print() {
	for (uchar i = 0; i < arrSizeY; ++i)
		for (uchar j = 0; j < arrSizeX; ++j)
			if (arr[i][j] && i + leftUpCorner.Y < output->GetScreenSizey() && j + leftUpCorner.X < output->GetScreenSizex())
				output[0][i + leftUpCorner.Y][j + leftUpCorner.X] = arr[i][j];
}

void MenuEnemy::SetFigure(char ** figure, uchar sizeX, uchar sizeY) {

}

void MenuEnemy::DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score) {
	for (auto &i : bullets) {
		if (i->GetUnused())
			continue;
		COORD pos = i->GetPos();
		if (pos.X < leftUpCorner.X + arrSizeX && pos.X >= leftUpCorner.X &&
			pos.Y < leftUpCorner.Y + arrSizeY && pos.Y >= leftUpCorner.Y)
			if (arr[pos.Y - leftUpCorner.Y][pos.X - leftUpCorner.X]) {
				arr[pos.Y - leftUpCorner.Y][pos.X - leftUpCorner.X] = 0;
				score->Change(1);
				i->Destroy();
			}
	}
}
