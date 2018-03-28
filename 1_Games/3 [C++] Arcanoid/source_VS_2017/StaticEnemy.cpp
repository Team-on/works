#include "precompiledHeaders.h"
#include "StaticEnemy.h"

StaticEnemy::StaticEnemy(screenScene *Output){
	turnCurrCooldown = 0;
	turnCooldown =  3 * 30;
	output = Output;
}


StaticEnemy::~StaticEnemy(){

}

//enum ClearReturn{AllDestroyed = 0,SomethingLeft, MenuStaticFigures, MenuEndlessFall, MenuAlien, MenuClassic, ClearReturnEND};
BasicEnemy::ClearReturn StaticEnemy::IsClear() const {
	for (uchar i = 0; i < arrSizeY; ++i) {
		for (uchar j = 0; j < arrSizeX; ++j) {
			if (arr[i][j] != 0)
				return SomethingLeft;
		}
	}
	return AllDestroyed;
}

void StaticEnemy::Turn() {
	if (++turnCurrCooldown == turnCooldown) {
		turnCurrCooldown = 0;
		for (uchar i = 0; i < arrSizeY; ++i)
			for (uchar j = 0; j < arrSizeX; ++j)
				if (i + leftUpCorner.Y < output->GetScreenSizey() && j + leftUpCorner.X < output->GetScreenSizex())
					output[0][i + leftUpCorner.Y][j + leftUpCorner.X] = 0;
		++leftUpCorner.Y;
	}
}

void StaticEnemy::Print() {
	for (uchar i = 0; i < arrSizeY; ++i) 
		for (uchar j = 0; j < arrSizeX; ++j) 
			if(arr[i][j] && i + leftUpCorner.Y < output->GetScreenSizey() && j + leftUpCorner.X < output->GetScreenSizex())
				output[0][i + leftUpCorner.Y][j + leftUpCorner.X] = arr[i][j];
}

void StaticEnemy::SetFigure(char ** figure, uchar sizeX, uchar sizeY) {
	if (arr != nullptr) {
		for (uchar i = 0; i < arrSizeY; ++i)
			delete[] arr[i];
		delete[] arr;
	}
	arr = figure;
	arrSizeY = sizeY;
	arrSizeX = sizeX;
}

void StaticEnemy::DestroyBlocks(vector <Bullet *> bullets, ScoreKeeper *score) {
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