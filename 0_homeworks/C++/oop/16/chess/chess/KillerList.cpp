#include "precompiledHeaders.h"
#include "KillerList.h"


KillerList::KillerList(){
	killers = new figureBasic*[16];
	killerSize = 0;
}

KillerList::KillerList(const KillerList &rhs) {
	killerSize = rhs.killerSize;
	killers = new figureBasic*[16];
	for (char i = 0; i < killerSize; ++i)
		killers[i] = rhs.killers[i];
}

KillerList::~KillerList(){
	delete[] killers;
}

void KillerList::AddKiller(figureBasic *fig) {
	killers[killerSize++] = fig;
}

void KillerList::operator=(const KillerList &rhs) {
	killerSize = rhs.killerSize;
	for (char i = 0; i < killerSize; ++i)
		killers[i] = rhs.killers[i];
}