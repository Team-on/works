#ifndef _KILLER_LIST_H_
#define _KILLER_LIST_H_

#include "figureBasic.h"

class KillerList{
	figureBasic **killers;
	char killerSize;
public:
	KillerList();
	KillerList(const KillerList &rhs);
	~KillerList();

	figureBasic *GetKiller(char pos) const { return killers[pos]; }

	char GetKillSize() const { return killerSize; }

	void AddKiller(figureBasic *fig);
	void operator=(const KillerList &rhs);
};

#endif