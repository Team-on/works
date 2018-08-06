#ifndef _BAR_H_
#define _BAR_H_

#include "screenObj.h"

class bar{
	int max, curr;
public:
	bar();
	~bar();

	void SetMax(int Max);
	void SerCurr(int Curr);

	int GetMax() const;
	int GetCurr() const;

	screenObj* GetOutputBar(outputStyle full, outputStyle empty, uchar length);

};

#endif // !_BAR_H_



