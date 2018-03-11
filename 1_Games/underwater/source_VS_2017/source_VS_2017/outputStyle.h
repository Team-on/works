#ifndef _OUTPUT_STYLE_H_
#define _OUTPUT_STYLE_H_

class outputStyle{
public:
	enum color {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
private:
	color fore, back;
public:
	outputStyle();
	outputStyle(const color Fore, const color Back);
	~outputStyle();

	void SetColor(const color Fore, const color Back);
	void SetConsoleColor() const;

	color GetFore() const { return fore; }
	color GetBack() const { return back; }

	bool operator==(outputStyle rhs) const;
	bool operator!=(outputStyle rhs) const;
};

#endif // !_OUTPUT_STYLE_H_
