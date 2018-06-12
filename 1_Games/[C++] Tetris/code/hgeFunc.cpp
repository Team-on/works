#include "preCompiled.h"
#include "hgeFunc.h"
#include "renderFunc.h"
#include "inputFunc.h"

bool GameFrameFunc() {
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
		soundMusic->Stop();
		return true;
	}

	if (GameInput()) {
		return true;
	}

	return false;
}

bool GameRenderFunc() {
	hge->Gfx_BeginScene();

	RenderGame();
	RenderGameInfo();

	hge->Gfx_EndScene();
	return false;
}


bool MenuFrameFunc() {
	return MenuInput();
}

bool MenuRenderFunc() {
	hge->Gfx_BeginScene();

	RenderMenu();
	hge->Gfx_EndScene();
	return false;
}


bool SettingsFrameFunc() {
	return SettingsInput();
}

bool SettingsRenderFunc() {
	hge->Gfx_BeginScene();

	RenderSettings();

	hge->Gfx_EndScene();
	return false;
}


bool CreditsFrameFunc() {
	return CreditsInput();
}

bool CreditsRenderFunc() {
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	RenderCredits();

	hge->Gfx_EndScene();
	return false;
}