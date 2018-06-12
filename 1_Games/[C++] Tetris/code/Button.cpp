#include "preCompiled.h"
#include "Button.h"


Button::Button(hgeQuad *_button, void(*_func)(void), HTEXTURE _hover){
	button = _button;
	func = _func;
	hover = _hover;
	standart = button->tex;
}


Button::~Button(){

}

void Button::CheckClick() {
	float x, y;
	hge->Input_GetMousePos(&x, &y);
	if (button->v[0].x <= x && x <= button->v[2].x &&
		button->v[0].y <= y && y <= button->v[2].y ){
		if (button->tex != hover)
			button->tex = hover;
		if (true == hge->Input_GetKeyState(HGEK_LBUTTON)) {
			func();
			Sleep(100);
		}
	}
	else if(button->tex != standart)
		button->tex = standart;
}

void Button::Render() {
	if(button->tex != NULL)
		hge->Gfx_RenderQuad(button);
}