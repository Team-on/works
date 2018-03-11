#include "precompiledHeaders.h"
#include "screenObj.h"


screenObj::screenObj() : symbol(0) {

}

screenObj::screenObj(const char Symbol) : symbol(Symbol) {

}
screenObj::screenObj(const outputStyle::color Fore, const outputStyle::color Back) : screenObj(0, Fore, Back) {

}
screenObj::screenObj(const char Symbol, const outputStyle::color Fore, const outputStyle::color Back) : symbol(Symbol), style(Fore, Back) {

}


screenObj::~screenObj(){

}

bool screenObj::operator==(screenObj &rhs) const {
	return ((symbol == rhs.symbol) && (style == rhs.style));
}
bool screenObj::operator!=(screenObj &rhs) const {
	return !(*this == rhs);
}

ostream& operator<<(ostream& out, screenObj& obj) {
	out << obj.symbol;
	return out;
}