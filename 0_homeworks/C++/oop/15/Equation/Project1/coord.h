#ifndef _COORD_H_
#define _COORD_H_

#include "Header.h"

struct coord {
	short x, y;
	coord();
	coord(short X, short Y);
};
ostream& operator<<(ostream &out, const coord &a);


#endif