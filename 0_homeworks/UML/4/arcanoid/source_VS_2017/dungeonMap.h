#ifndef _DUNGEON_MAP_H_
#define _DUNGEON_MAP_H_

#include "dungeonCell.h"

class dungeonMap {
	const usint sizex, sizey;
	dungeonCell **map;

public:
	dungeonMap();
	dungeonMap(usint Sizex, usint Sizey);
	~dungeonMap();

	const usint GetSizex() const;
	const usint GetSizey() const;

	//Обнуляє все установлене на карту. Скидає вивід до ланшафту
	void SetDisplayBasic();

	dungeonCell *& operator[](usint i) const;
};

#endif // !_DUNGEON_MAP_H_
