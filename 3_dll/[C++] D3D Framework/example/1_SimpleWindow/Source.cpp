#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "../../D3D Framework/D3DFramework.h"
#pragma comment(lib, "../../lib/D3D Framework_32_d.lib")

using namespace dxFramework::Framework;
using namespace dxFramework::Input;
using namespace dxFramework::Render;
using namespace dxFramework::Util;

class MyInput : public InputListener{
public:
	bool KeyPressed(const KeyEvent &arg){
		printf("key press %c\n", arg.wc);
		return false;
	}

	bool
		MouseMove(const MouseEvent &arg){
		printf("mouse %d - %d\n", arg.x, arg.y);
		return false;
	}
};

class MyRender : public Render{
public:
	bool Init(HWND nwnd){ return true; }
	bool Draw(){ return true; }
	void Close(){}
};

int main(){
	Framework framework;

	framework.SetRender(new MyRender());
	framework.Init();
	framework.AddInputListener(new MyInput());

	framework.Run();

	framework.Close();

	int tmp;
	scanf("%d", &tmp);
	return 0;
}