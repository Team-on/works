#include "precompiledHeaders.h"
#include "dungeonMap.h"


dungeonMap::dungeonMap() : sizex(0), sizey(0)  {
	map = nullptr;
}

dungeonMap::dungeonMap(usint Sizex, usint Sizey) : sizex(Sizex), sizey(Sizey), map(new dungeonCell*[sizey]) {
	for (usint i = 0; i < sizey; ++i)
		map[i] = new dungeonCell[sizex];
}

dungeonMap::~dungeonMap(){
	if (map != nullptr) {
		for (usint i = 0; i < sizey; ++i)
			delete[] map[i];
		delete[] map;
	}
}

const usint dungeonMap::GetSizex() const {
	return sizex;
}
const usint dungeonMap::GetSizey() const {
	return sizey;
}

void dungeonMap::SetDisplayBasic() {
	for (usint i = 0; i < sizey; ++i)
		for (usint j = 0; j < sizex; ++j) {
			map[i][j].SetDisplaySymbol(map[i][j].GetBasicSymbol());
			map[i][j].SetDisplayColor(map[i][j].GetBasicColor());
		}
}

dungeonCell *& dungeonMap::operator[](usint i) const {
	return map[i];
}
