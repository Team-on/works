#include "precompiledHeaders.h"
#include "BasicEnemy.h"

#include "StaticEnemy.h"
#include "MenuEnemy.h"
#include "EndlessEnemy.h"
#include "ClassicEnemy.h"
#include "AlienEnemy.h"


BasicEnemy::BasicEnemy() {
	arr = nullptr;
	arrSizeX = arrSizeY = 0;
	leftUpCorner.X = leftUpCorner.Y = 1;
}

BasicEnemy::~BasicEnemy(){
	if (arr != nullptr) {
		for (uchar i = 0; i < arrSizeY; ++i)
			delete[] arr[i];
		delete[] arr;
	}
}

uchar BasicEnemy::LowestBlockPosY() const {
	for (uchar i = arrSizeY - 1; i >= 0 ; --i) 
		for (uchar j = 0; j < arrSizeX; ++j)
			if(arr != nullptr)
			if (arr[i][j] != 0)
				return i + leftUpCorner.Y;
	return 1;
}

BasicEnemy * BasicEnemy::CreateEnemy(BasicEnemy::ClearReturn type, screenScene *output) {
	switch (type){
	case BasicEnemy::MenuStaticFigures:
	{
		StaticEnemy * enemy = new StaticEnemy(output);
		const uchar sizeX = 38, sizeY = 11;
		char **map = new char*[sizeY];
		switch (rand() % 10){
		case 0:
		{
#define $ '$'
			char mapTmp[sizeY][sizeX] = {
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};
#undef $
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = mapTmp[i][j];
			}
		}
			break;
		case 1:
		{
#define $ '$'
			char mapTmp[sizeY][sizeX] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, $, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, $, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, $, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, $, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, $, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, $, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, 0, 0, 0, 0, 0, 0, 0, 0, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};
#undef $
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = mapTmp[i][j];
			}
		}
			break;
		case 2:
		{
#define $ '$'
			char mapTmp[sizeY][sizeX] = {
			{ 0, 0, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, 0, 0 },
			{ 0, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, 0 },
			{ $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $ },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $ },
			{ 0, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, 0 },
			{ 0, 0, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};
#undef $
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = mapTmp[i][j];
			}
		}
			break;
		case 3:
		{
#define $ '$'
			char mapTmp[sizeY][sizeX] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0 },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $ },
			{ 0, 0, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, $, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};
#undef $
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = mapTmp[i][j];
			}
		}
			break;
		case 4:
		{
#define $ '$'
			char mapTmp[sizeY][sizeX] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, $, $, $, 0, 0, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, $, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, $, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, $, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, 0, 0, 0, 0, 0, 0, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, $, $, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, $, $, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};
#undef $
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = mapTmp[i][j];
			}
		}
			break;
		case 5:
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = j % 2 == i % 2? '$':0;
			}
			break;
		case 6:
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = rand() % 9 == 0 ? '$' : 0;
			}
			break;
		case 7:
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = rand() % 7 == 0 ? '$' : 0;
			}
			break;
		case 8:
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = rand() % 5 == 0 ? '$' : 0;
			}
			break;
		case 9:
			for (uchar i = 0; i < sizeY; ++i) {
				map[i] = new char[sizeX];
				for (uchar j = 0; j < sizeX; ++j)
					map[i][j] = rand() % 3 == 0?'$':0;
			}
			break;
		}
		/*
		char mapTmp[sizeY][sizeX] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		};
		for (uchar i = 0; i < sizeY; ++i) {
			map[i] = new char[sizeX];
			for (uchar j = 0; j < sizeX; ++j)
				map[i][j] = mapTmp[i][j];
		}
		*/
		enemy->SetFigure((char **)map, sizeX, sizeY);
		return enemy;
	}
	case BasicEnemy::MenuEndlessFall:
		return new EndlessEnemy(output);
	case BasicEnemy::MenuAlien:
		//return new AlienEnemy(output);
	case BasicEnemy::MenuClassic:
		//return new ClassicEnemy(output);
	case BasicEnemy::MenuLevel:
		return new MenuEnemy(output);
	}
	throw exception("Error. BasicEnemy::CreateEnemy(ClearReturn type). type is incorrect");
}