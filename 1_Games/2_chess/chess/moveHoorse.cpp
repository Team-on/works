#include "precompiledHeaders.h"
#include "moveHoorse.h"


bool moveHoorse::CanMove(COORD from, COORD to) {
	COORD shift = { abs(from.X - to.X),  abs(from.Y - to.Y) };

	if (shift.X > shift.Y) 
		swap(shift.X, shift.Y);

	if (shift.X == 1 && shift.Y == 2)
		return 1;

	return 0;
}
