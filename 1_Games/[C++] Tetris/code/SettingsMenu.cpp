#include "preCompiled.h"
#include "SettingsMenu.h"


SettingsMenu::SettingsMenu(){
	Menu::FormBackgroundQuad(backgroundQuad);
	Menu::FormBackgroundQuad(sndPosQuad);
	Menu::FormBackgroundQuad(musPosQuad);
	Menu::FormBackgroundQuad(activePosQuad);

	backgroundQuad->tex = hge->Texture_Load("menu\\settings\\back.png");
	sndPosQuad->tex = hge->Texture_Load("menu\\settings\\sound100.png");
	musPosQuad->tex = hge->Texture_Load("menu\\settings\\music50.png");
	activePosQuad->tex = hge->Texture_Load("menu\\settings\\musicActive.png");
}


SettingsMenu::~SettingsMenu(){

}

void SettingsMenu::Render() {
	hge->Gfx_RenderQuad(backgroundQuad);
	hge->Gfx_RenderQuad(musPosQuad);
	hge->Gfx_RenderQuad(sndPosQuad);
	hge->Gfx_RenderQuad(activePosQuad);
}

bool SettingsMenu::Input() {
	if (hge->Input_GetKeyState(HGEK_ESCAPE) || (activePos == 2 && hge->Input_GetKeyState(HGEK_ENTER))) {
		hge->Gfx_BeginScene();
		MenuRenderFunc();
		hge->Gfx_EndScene();
		activePos = 0;
		SetNewActivePos();
		return true;
	}

	Sleep(100);
	if (hge->Input_GetKeyState(HGEK_LEFT)) {
		if (activePos == 0) {
			--musPos;
			if (musPos == -1)
				musPos = 2;
			SetNewMusPos();
		}
		else if (activePos == 1) {
			--sndPos;
			if (sndPos == -1)
				sndPos = 2;
			SetNewSndPos();
		}
	}
	else if (hge->Input_GetKeyState(HGEK_RIGHT)) {
		if (activePos == 0) {
			++musPos;
			if (musPos == 3)
				musPos = 0;
			SetNewMusPos();
		}
		else if(activePos == 1) {
			++sndPos;
			if(sndPos == 3)
				sndPos = 0;
			SetNewSndPos();
		}
	}
	else if (hge->Input_GetKeyState(HGEK_UP)) {
		--activePos;
		if (activePos == -1)
			activePos = 2;
		SetNewActivePos();
	}
	else if (hge->Input_GetKeyState(HGEK_DOWN)) {
		++activePos;
		if (activePos == 3)
			activePos = 0;
		SetNewActivePos();
	}
	return false;
}

void SettingsMenu::SetNewActivePos() {
	hge->Texture_Free(activePosQuad->tex);
	if(activePos == 0)
		activePosQuad->tex = hge->Texture_Load("menu\\settings\\musicActive.png");
	else if (activePos == 1)
		activePosQuad->tex = hge->Texture_Load("menu\\settings\\soundActive.png");
	else if (activePos == 2)
		activePosQuad->tex = hge->Texture_Load("menu\\settings\\backActive.png");
}

void SettingsMenu::SetNewSndPos() {
	hge->Texture_Free(sndPosQuad->tex);
	if (sndPos == 0) {
		sndPosQuad->tex = hge->Texture_Load("menu\\settings\\sound100.png");
		soundSound->volumeSound = 1.f;
	}
	else if (sndPos == 1) {
		sndPosQuad->tex = hge->Texture_Load("menu\\settings\\sound50.png");
		soundSound->volumeSound = 0.5f;
	}
	else if (sndPos == 2) {
		sndPosQuad->tex = hge->Texture_Load("menu\\settings\\sound0.png");
		soundSound->volumeSound = 0.f;
	}
}

void SettingsMenu::SetNewMusPos() {
	hge->Texture_Free(musPosQuad->tex);
	if (musPos == 0) {
		musPosQuad->tex = hge->Texture_Load("menu\\settings\\music100.png");
		soundSound->volumeMusic = 1.f;
	}
	else if (musPos == 1) {
		musPosQuad->tex = hge->Texture_Load("menu\\settings\\music50.png");
		soundSound->volumeMusic = 0.5f;
	}
	else if (musPos == 2) {
		musPosQuad->tex = hge->Texture_Load("menu\\settings\\music0.png");
		soundSound->volumeMusic = 0.f;
	}
}