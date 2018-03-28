#ifndef _LOG_H_
#define _LOG_H_

class LOG_GAME {
private:
	const usint logHistorySize;
	usint head;
	string *log;

public:
	LOG_GAME(const usint LogHistorySize);
	~LOG_GAME();

	void LogAdd(string str);
	string LogGet(usint i);
};

#endif // !_LOG_H_



