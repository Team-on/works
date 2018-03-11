#include "precompiledHeaders.h"
#include "LOG.h"


LOG_GAME::LOG_GAME(const usint LogHistorySize) : logHistorySize(LogHistorySize), log(new string[logHistorySize]) {
	head = 0;
	log[0] = " ";
}


LOG_GAME::~LOG_GAME(){
}


void LOG_GAME::LogAdd(string str) {
	if(head + 1 == logHistorySize){
		uchar i = 0;
		for(; i <= 11; ++i)
			log[i] = log[logHistorySize - i - 1];
		head = i;
	}
	log[++head] = str;
}
string LOG_GAME::LogGet(usint i) {
	if (head - i < 0)
		return "";
	return log[head - i];
}
