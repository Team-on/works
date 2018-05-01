#ifndef _DUNGEON_CELL_H_
#define _DUNGEON_CELL_H_

#include "outputStyle.h"

class dungeonCell {
	char displaySymbol;
	char basicSymbol;
	outputStyle displayColor;
	outputStyle basicColor;

	bool isSolid;
public:
	dungeonCell();
	dungeonCell(char BasicSymbol, outputStyle Color);
	~dungeonCell();

	void SetDisplaySymbol(char sym);
	void SetBasicSymbol(char sym);
	void SetDisplayColor(outputStyle Color);
	void SetBasicColor(outputStyle Color);

	void SetIsSolid(bool solid);

	char GetDisplaySymbol() const;
	char GetBasicSymbol() const;
	outputStyle GetDisplayColor() const;
	outputStyle GetBasicColor() const;

	bool GetIsSolid() const;
};

#endif // !_DUNGEON_CELL_H_




