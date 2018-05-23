#include "preCompiled.h"

#include "menu.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, int argc){
	screenSize.x = 800;
	screenSize.y = 600;

	hge = hgeCreate(HGE_VERSION);
	
	hge->System_SetState(HGE_LOGFILE, "tetris.log");
	hge->System_SetState(HGE_TITLE, "WarTetris");
	hge->System_SetState(HGE_ICON, "icon.ico");
	
	hge->System_SetState(HGE_SCREENWIDTH, screenSize.x);
	hge->System_SetState(HGE_SCREENHEIGHT, screenSize.y);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_FPS, 30);
	hge->System_SetState(HGE_WINDOWED, true);

	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_DONTSUSPEND, false);
	
	hge->System_SetState(HGE_EXITFUNC, []()->bool {soundMusic->Stop(); return true; });
	hge->System_SetState(HGE_FOCUSGAINFUNC, []()->bool {soundMusic->Play(); return NULL; });
	hge->System_SetState(HGE_FOCUSLOSTFUNC, []()->bool {soundMusic->Stop(); return NULL; });

	hge->System_SetState(HGE_USESOUND, false);


	if (hge->System_Initiate()){
		srand((unsigned int)time(NULL));

		menu = new Menu();
		menu->StartMenu();
	}
	else 
		MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_SYSTEMMODAL | MB_ICONERROR | MB_OK );

	hge->System_Shutdown();
	hge->Release();
	return 0;
}
