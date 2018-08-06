#include "precompiledHeaders.h"
#include "LOG.h"


LOG_GAME::LOG_GAME(const usint LogHistorySize) : logHistorySize(LogHistorySize), log(new string[logHistorySize]) {
	logType = Log_Small;
	head = 0;
	log[0] = "Log init";
}


LOG_GAME::~LOG_GAME(){
}

void LOG_GAME::SetLogType(LOG_GAME::LOG_TYPE newType) {
	logType = newType;
}

LOG_GAME::LOG_TYPE LOG_GAME::GetLogType() const {
	return logType;
}

void LOG_GAME::LogAdd(string str) {
	if(head + 1 == logHistorySize){
		for(uchar i = 0; i <= 100; ++i)
			log[i] = log[logHistorySize - i - 1];
		head = 100;
	}
	log[++head] = str;
}
string LOG_GAME::LogGet(usint i) {
	if (head - i < 0)
		return "";
	return log[head - i];
}
