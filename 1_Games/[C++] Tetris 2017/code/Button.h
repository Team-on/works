#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button{
	hgeQuad *button;
	HTEXTURE hover, standart;
	void (*func)(void);
public:
	Button(hgeQuad *_button, void(*_func)(void), HTEXTURE hover);
	~Button();

	void CheckClick();
	void Render();
};

#endif