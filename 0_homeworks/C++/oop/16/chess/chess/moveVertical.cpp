#include "precompiledHeaders.h"
#include "moveVertical.h"


bool moveVertical::CanMove(COORD from, COORD to) {
	if (from.Y == to.Y)
		return 1;
	return 0;
}