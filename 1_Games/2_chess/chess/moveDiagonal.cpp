#include "precompiledHeaders.h"
#include "moveDiagonal.h"


bool moveDiagonal::CanMove(COORD from, COORD to) {
	if (abs(from.Y - to.Y) == abs(from.X - to.X))
		return 1;
	return 0;
}
