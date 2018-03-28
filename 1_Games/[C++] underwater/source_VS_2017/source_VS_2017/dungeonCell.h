#ifndef _DUNGEON_CELL_H_
#define _DUNGEON_CELL_H_

#include "outputStyle.h"

class dungeonCell {
	char displaySymbol;
	char basicSymbol;
	outputStyle displayColor;
	outputStyle basicColor;

	bool isSolid;
	bool isLightSolid;
public:
	dungeonCell();
	dungeonCell(char BasicSymbol, outputStyle Color);
	~dungeonCell();

	void SetIsSolid(bool solid);
	void SetIsLightSolid(bool IsLightSolid);

	bool GetIsSolid() const;
	bool GetIsLightSolid() const;

	void SetDisplaySymbol(char sym);
	void SetBasicSymbol(char sym);
	void SetDisplayColor(outputStyle Color);
	void SetBasicColor(outputStyle Color);

	char GetDisplaySymbol() const;
	char GetBasicSymbol() const;
	outputStyle GetDisplayColor() const;
	outputStyle GetBasicColor() const;
};

#endif // !_DUNGEON_CELL_H_




