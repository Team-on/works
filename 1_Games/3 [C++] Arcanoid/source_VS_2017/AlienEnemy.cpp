#include "precompiledHeaders.h"
#include "AlienEnemy.h"

AlienEnemy::AlienEnemy(screenScene *Output) {
	turnCooldown = 3 * 30;
	output = Output;
	leftUpCorner.X = leftUpCorner.Y = 1;
	arrSizeX = 38;
	arrSizeY = Output->GetScreenSizey() - 2;
	arr = new char*[arrSizeY];
	for (uchar i = 0; i < arrSizeY; ++i) {
		arr[i] = new char[arrSizeX];
		for (uchar j = 0; j < arrSizeX; ++j)
			arr[i][j] = 0;
	}
}


AlienEnemy::~AlienEnemy() {

}

//enum ClearReturn{AllDestroyed = 0,SomethingLeft, MenuStaticFigures, MenuEndlessFall, MenuAlien, MenuClassic, ClearReturnEND};
BasicEnemy::ClearReturn AlienEnemy::IsClear() const {
	for (uchar i = 0; i < arrSizeY; ++i) {
		for (uchar j = 0; j < arrSizeX; ++j) {
			if (arr[i][j] != 0)
				return SomethingLeft;
		}
	}
	return AllDestroyed;
}

void AlienEnemy::Turn() {
	if (++turnCurrCooldown == turnCooldown) {
		turnCurrCooldown = 0;
		char tmp;
		for (uchar i = arrSizeY - 1; i > 0; --i) {
			for (uchar j = 0; j < arrSizeX; ++j) {
				arr[i][j] = arr[i - 1][j];
				output[0][i + leftUpCorner.Y][j + leftUpCorner.X] = 0;
			}
		}

	}
}

void AlienEnemy::Print() {
	for (uchar i = 0; i < arrSizeY; ++i)
		for (uchar j = 0; j < arrSizeX; ++j)
			if (arr[i][j] && i + leftUpCorner.Y < output->GetScreenSizey() && j + leftUpCorner.X < output->GetScreenSizex())
				output[0][i + leftUpCorner.Y][j + leftUpCorner.X] = arr[i][j];
}

void AlienEnemy::DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score) {
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