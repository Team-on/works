#include "precompiledHeaders.h"
#include "func.h"

bool operator==(COORD a, COORD b) {
	return (a.X == b.X) && (a.Y == b.Y);
}
bool operator!=(COORD a, COORD b) {
	return !(a==b);
}