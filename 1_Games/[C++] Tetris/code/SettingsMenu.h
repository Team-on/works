#ifndef _SETTINGS_MENU_H_
#define _SETTINGS_MENU_H_

class SettingsMenu{
public:
	SettingsMenu();
	~SettingsMenu();

	void Render();
	bool Input();

private:
	hgeQuad *backgroundQuad;
	int sndPos = 1, musPos = 0, activePos = 0;
	hgeQuad *sndPosQuad, *musPosQuad, *activePosQuad;

	void SetNewActivePos();
	void SetNewSndPos();
	void SetNewMusPos();
};

#endif