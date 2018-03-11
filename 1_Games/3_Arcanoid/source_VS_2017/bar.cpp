#include "precompiledHeaders.h"
#include "bar.h"


bar::bar(){
	curr = max = 0;
}

bar::~bar(){

}

void bar::SetMax(int Max) {
	max = Max;
}
void bar::SerCurr(int Curr) {
	curr = Curr;
	if (curr > max)
		curr = max;
}

int bar::GetMax() const {
	return max;
}
int bar::GetCurr() const {
	return curr;
}

screenObj* bar::GetOutputBar(outputStyle full, outputStyle empty, uchar length) {\
	uint fullPersent = round(double(curr) / max * 100);

	screenObj *rezult = new screenObj[length];

	char *str = new char[10];
	_itoa(curr, str, 10);
	uchar currNumPos = 0;
	string num = str;
	num += " / ";
	_itoa(max, str, 10);
	num += str;
	delete[] str;

	for (uchar i = 0; i < length; ++i) {
		if (i <= round(float(length) / 100 * fullPersent)) {
			rezult[i].SetStyle(full);
		}
		else {
			rezult[i].SetStyle(empty);
		}
		
		if (i >= length / 2 - num.find('/') && currNumPos < num.length()) {
			rezult[i].SetSymbol(num[currNumPos++]);
		}
	}

	return rezult;
}
