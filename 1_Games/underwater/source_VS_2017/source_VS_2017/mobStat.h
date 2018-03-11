#ifndef _MOB_STAT_H_
#define _MOB_STAT_H_

class mobStat {
	short base, curr;
public:
	mobStat();
	~mobStat();

	void SetBase(short base);
	void SetCurr(short curr);

	short GetBase() const;
	short GetCurr() const;
};

#endif // !_MOB_STAT_H_



