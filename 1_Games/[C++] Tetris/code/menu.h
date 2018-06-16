#ifndef _MENU_H_
#define _MENU_H_

#include "game.h"
#include "hgeFunc.h"
#include "SettingsMenu.h"

class Menu{
public:
	enum MENU_CHOOSE : char { ChooseNewGame, ChooseLoadGame, ChooseHighScore, ChooseSettings, ChooseCredits, ChooseExit, ChooseNone };
private:
	MENU_CHOOSE lastChoose;
	hgeQuad *menuQuad, *creditsQuad;
	HTEXTURE texture[MENU_CHOOSE::ChooseNone + 1];

	SettingsMenu *settingsMenu;

public:
	Menu();
	~Menu();

	void StartMenu();

	//------------------------- Output--------------------------------
	hgeQuad *GetCreditsQuad();
	hgeQuad *GetMenuQuad();

	SettingsMenu * GetSettingsMenu() { return settingsMenu; }

	//------------------------- Input --------------------------------
	void MoveDown();
	void MoveUp();

	void SetLastChooseToExit() { lastChoose = MENU_CHOOSE::ChooseExit; }

private:
	//------------------------- Menu puncts Func --------------------------------
	void StartGame();
	void LoadGame();
	void HighScore();
	void Settings();
	void Credits();
	bool Exit();


	//-------------------------- Other -----------------------------
public:
	static void FormBackgroundQuad(hgeQuad *&quad);
};

#endif
