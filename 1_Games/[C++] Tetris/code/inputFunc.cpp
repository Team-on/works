#include "preCompiled.h"
#include "inputFunc.h"

bool GameInput() {
	if(game != nullptr){
		if (game->CheckExit())
			return true;		

		float dt = hge->Timer_GetTime();

		if (HGEK_P == hge->Input_GetKey()) {
			game->isPaused = !game->isPaused;
			difficult->SetLastTimerNonGame(dt);
			difficult->SetLastTimer(dt);
		}

		game->CheckButtons();

		if (game->isPaused)
			return false;


		if (dt - difficult->GetReaction() / 2 > difficult->GetLastTimerNonGame()) {
			if (hge->Input_GetKeyState(HGEK_SPACE)) {
				difficult->SetLastTimerNonGame(dt);
				game->Rotate();
			}
		}

		if (hge->Input_GetKeyState(HGEK_LEFT))
			inputQueue->SetKey(InputQueue::InputKey::ArrowLeft);
		if (hge->Input_GetKeyState(HGEK_RIGHT))
			inputQueue->SetKey(InputQueue::InputKey::ArrowRight);

		if (dt - difficult->GetReaction() > difficult->GetLastTimer()) {
			difficult->SetLastTimer(dt);

			InputQueue::InputKey key = inputQueue->GetKey();
			if (key == InputQueue::InputKey::ArrowLeft)
				game->MoveLeft();
			if (key == InputQueue::InputKey::ArrowRight)
				game->MoveRight();
			if (hge->Input_GetKeyState(HGEK_DOWN))
				difficult->SetLastTimer(dt - difficult->GetReaction() / 2);

			if (!game->Loop())
				return true;

			Sleep(100);
		}
	}
	return false;
}

bool MenuInput() {
	if (HGEK_DOWN == hge->Input_GetKey())
		menu->MoveDown();
	else if (HGEK_UP == hge->Input_GetKey())
		menu->MoveUp();

	if (true == hge->Input_GetKeyState(HGEK_ESCAPE)) {
		menu->SetLastChooseToExit();
		return true;
	}

	if (HGEK_ENTER == hge->Input_GetKey() || HGEK_SPACE == hge->Input_GetKey()) {
		return true;
	}

	return false;
}

bool SettingsInput() {
	return menu->GetSettingsMenu()->Input();
}

bool CreditsInput() {
	if (hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	return false;
}