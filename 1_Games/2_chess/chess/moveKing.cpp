#include "precompiledHeaders.h"
#include "moveKing.h"


bool moveKing::CanMove(COORD from, COORD to) {
	if (abs(from.X - to.X) <= 1 && abs(from.Y - to.Y) <= 1)
		return 1;
	return 0;
}
