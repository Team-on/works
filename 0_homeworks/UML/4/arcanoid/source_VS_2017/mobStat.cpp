#include "precompiledHeaders.h"
#include "mobStat.h"


mobStat::mobStat(){
	base = curr = 0;
}


mobStat::~mobStat(){

}

void mobStat::SetBase(short Base) {
	curr -= base;
	base = Base;
	curr += base;
}
void mobStat::SetCurr(short Curr) {
	curr = Curr;
}

short mobStat::GetBase() const {
	return base;
}
short mobStat::GetCurr() const {
	return curr;
}
