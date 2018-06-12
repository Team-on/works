#include "preCompiled.h"
#include "menu.h"

Menu::Menu(){
	lastChoose = ChooseNewGame;

	string pathBase = "menu\\menu\\menu";
	string path;
	for (unsigned char i = 0; i <= Menu::ChooseNone; ++i) {
		path = pathBase;
		path += i + '0';
		path += ".png";
		this->texture[i] = hge->Texture_Load(path.c_str());
	}

	FormBackgroundQuad(menuQuad);
	menuQuad->tex = texture[lastChoose];

	FormBackgroundQuad(creditsQuad);
	creditsQuad->tex = hge->Texture_Load("menu\\credits\\back.png");

	settingsMenu = new SettingsMenu();
}


Menu::~Menu(){
	hge->Texture_Free(menuQuad->tex);
	delete menuQuad;
}

void Menu::StartMenu() {
REPEAT_MENU_2:
	hge->System_SetState(HGE_FRAMEFUNC, MenuFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, MenuRenderFunc);
	hge->System_Start();
	
	auto choose = lastChoose;
	lastChoose = Menu::MENU_CHOOSE(0);

	switch (choose) {
	case Menu::ChooseNewGame:
		StartGame();
		goto REPEAT_MENU;
	case Menu::ChooseLoadGame:
		LoadGame();
		goto REPEAT_MENU;
	case Menu::ChooseHighScore:
		HighScore();
		goto REPEAT_MENU;
	case Menu::ChooseSettings:
		Settings();
		goto REPEAT_MENU;
	case Menu::ChooseCredits:
		Credits();
		goto REPEAT_MENU;
	case Menu::ChooseExit:
		if(Exit())
			return;
		goto REPEAT_MENU;
	case Menu::ChooseNone:
		goto REPEAT_MENU;
	}
REPEAT_MENU:
	Sleep(250);
	goto REPEAT_MENU_2;
}

hgeQuad * Menu::GetCreditsQuad() {
	return creditsQuad;
}

hgeQuad * Menu::GetMenuQuad() {
	if (texture[lastChoose] != menuQuad->tex)
		menuQuad->tex = texture[lastChoose];
	return menuQuad;
}

void Menu::MoveDown() {
	lastChoose = Menu::MENU_CHOOSE(lastChoose + 1);
	if (lastChoose >= Menu::MENU_CHOOSE::ChooseNone)
		lastChoose = Menu::MENU_CHOOSE(0);
	
}

void Menu::MoveUp() {
	lastChoose = Menu::MENU_CHOOSE(lastChoose - 1);
	if (lastChoose < 0)
		lastChoose = Menu::MENU_CHOOSE(Menu::MENU_CHOOSE::ChooseNone - 1);
}


void Menu::StartGame() {
	if (game == nullptr) {
		soundMusic = new SoundMusic;
		soundSound = new SoundSound;
		tetrisFigure::LoadFromXml();
		game = new Game;
		game->Init();
		gameInfo = new GameInfo();
		difficult = new Difficult(0.4f, 0.01f, 0.1f, 10);
	}
	else {
		game->Reload();
		gameInfo->Reload();
		difficult->Reload();
	}
	soundSound->Play("sounds\\GameStart.ogg");
	soundMusic->Play("sounds\\MainTheme.mp3");
	hge->System_SetState(HGE_FRAMEFUNC, GameFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, GameRenderFunc);
	hge->System_Start();
}

void Menu::LoadGame() {
	if (game == nullptr) {
		soundMusic = new SoundMusic;
		soundSound = new SoundSound;
		tetrisFigure::LoadFromXml();
		game = new Game;
		game->Init();
		gameInfo = new GameInfo();
		difficult = new Difficult(0.4f, 0.01f, 0.1f, 10);
	}
	else {
		game->Reload();
		gameInfo->Reload();
		difficult->Reload();
	}
	soundSound->Play("sounds\\GameStart.ogg");
	soundMusic->Play("sounds\\MainTheme.mp3");
	game->Load();
	hge->System_SetState(HGE_FRAMEFUNC, GameFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, GameRenderFunc);
	hge->System_Start();
}

void Menu::HighScore() {

}

void Menu::Settings() {
	hge->System_SetState(HGE_FRAMEFUNC, SettingsFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, SettingsRenderFunc);
	hge->System_Start();
}

void Menu::Credits() {
	hge->System_SetState(HGE_FRAMEFUNC, CreditsFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, CreditsRenderFunc);
	hge->System_Start();
}

bool Menu::Exit() {
	return true;
}


void Menu::FormBackgroundQuad(hgeQuad *&quad) {
	quad = new hgeQuad();
	quad->blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;

	quad->v[0].tx = 0.f; quad->v[0].ty = 0.f;
	quad->v[1].tx = 1.f; quad->v[1].ty = 0.f;
	quad->v[2].tx = 1.f; quad->v[2].ty = 1.f;
	quad->v[3].tx = 0.f; quad->v[3].ty = 1.f;

	quad->v[0].x = 0.f; quad->v[0].y = 0.f;
	quad->v[1].x = (float)screenSize.x; quad->v[1].y = 0.f;
	quad->v[2].x = (float)screenSize.x; quad->v[2].y = (float)screenSize.y;
	quad->v[3].x = 0.f; quad->v[3].y = (float)screenSize.y;

	DWORD color = hgeColor(1, 1, 1, 1).GetHWColor();
	for (int j = 0; j < 4; j++) {
		quad->v[j].z = 0.5f;
		quad->v[j].col = color;
	}
}