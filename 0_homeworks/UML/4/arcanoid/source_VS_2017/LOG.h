#ifndef _LOG_H_
#define _LOG_H_

class LOG_GAME {
public:
	enum LOG_TYPE {
		Log_Big = 1,
		Log_Small,
		Log_None,
		LOG_TYPES_CNT
	};
private:
	const usint logHistorySize;
	usint head;
	LOG_TYPE logType;
	string *log;

public:
	LOG_GAME(const usint LogHistorySize);
	~LOG_GAME();

	void SetLogType(LOG_TYPE newType);

	LOG_TYPE GetLogType() const;

	void LogAdd(string str);
	string LogGet(usint i);
};

#endif // !_LOG_H_



