#ifndef _SCREEN_OBJ_H_
#define _SCREEN_OBJ_H_

#include "outputStyle.h"

class screenObj{
	char symbol;
	outputStyle style;
public:
	screenObj();
	screenObj(const char Symbol);
	screenObj(const outputStyle::color Fore, const outputStyle::color Back);
	screenObj(const char Symbol, const outputStyle::color Fore, const outputStyle::color Back);
	~screenObj();

	void			SetStyle	(const outputStyle& Style)			{ style = Style; }
	outputStyle		GetStyle	()							const	{ return style; }

	void			SetSymbol	(const char Symbol)					{ symbol = Symbol; }
	char			GetSymbol	()							const	{ return symbol; }

	bool operator==(screenObj &rhs) const;
	bool operator!=(screenObj &rhs) const;

	friend ostream& operator<<(ostream& out, screenObj& obj);
};

#endif // !_SCREEN_OBJ_H_