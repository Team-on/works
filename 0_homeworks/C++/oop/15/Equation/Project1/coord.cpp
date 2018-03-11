#include "coord.h"

coord::coord() {
	x = y = 0;
}
coord::coord(short X, short Y) {
	x = X;
	y = Y;
}

ostream& operator<<(ostream &out, const coord &a) {
	out << '(' << a.x << ';' << a.y << ')';
	return out;
}