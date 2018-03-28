#include "precompiledHeaders.h"
#include "moveHorisontal.h"


bool moveHorisontal::CanMove(COORD from, COORD to) {
	if (from.X == to.X)
		return 1;
	return 0;
}