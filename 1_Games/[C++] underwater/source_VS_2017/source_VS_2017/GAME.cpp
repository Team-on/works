#include "precompiledHeaders.h"

#include "GAME.h"


GAME::GAME(uchar screenSizex, uchar screenSizey) : output(screenSizex, screenSizey), room(200, 100) {
	isRunning = 1;
	mainMenuBack = 0;

	output.SetTitle("UnderWater");
	output.MaximizeWindow();
	output.ClearScr();

	LogInit();

	room.SetPlayerPrt(player);

	room.GenerateRandomMaze();
	player.SetPos({ 150, 50 });
	camPos = player.GetPos();

	player.reaction.SetBase(1000);
	player.lengthOfView.SetBase(10);

	gameTime.SetTicTimerStep(room.CalcTicTimerStep());
	gameTime.SetTicTimerMax(room.CalcTicTimerMax());
}

GAME::~GAME(){
	output.BeforeExit();
}

void GAME::MainLoop() {
	if (0 /*Хтось помер, повод змінити шаг таймера*/) {
		gameTime.SetTicTimerStep(room.CalcTicTimerStep());
		gameTime.SetTicTimerMax(room.CalcTicTimerMax());
	}

	ullint currTicCnt = gameTime.Tic();

	if (currTicCnt % player.reaction.GetCurr() == 0) {
		PrintCurrState();
		DoPlayerTurn();
		PrintCurrState();
	}

	room.DoMobTurns(currTicCnt);
}

void GAME::DoPlayerTurn() {
INVALID_TURN_REPEAT_TURN:
UI_TURN:

	int turn = WaitForInput();

	COORD moveDirection[4] = {
	{ player.GetPos().X - 1 , player.GetPos().Y },
	{ player.GetPos().X + 1 , player.GetPos().Y },
	{ player.GetPos().X , player.GetPos().Y + 1 },
	{ player.GetPos().X , player.GetPos().Y - 1 }
	};
	direction currDir = (
		turn == VK_LEFT		? direction::LEFT :
		(turn == VK_RIGHT	? direction::RIGHT :
		(turn == VK_DOWN	? direction::DOWN :
		(turn == VK_UP		? direction::UP :
		(turn == 'a'		? direction::LEFT :
		(turn == 'd'		? direction::RIGHT :
		(turn == 's'		? direction::DOWN :
		(turn == 'w'		? direction::UP :
			direction::NONE_DIR
		))))))));

	//Attack & move
	if (currDir != direction::NONE_DIR) {
		//Attack 
		_mobBasic *currEnemy = room.MobOnPos(moveDirection[currDir]);
		if (currEnemy != nullptr) {

			string logRecord = "Atack -> ";
			switch (currDir) {
			case LEFT:
				logRecord += "left";
				break;
			case RIGHT:
				logRecord += "right";
				break;
			case DOWN:
				logRecord += "down";
				break;
			case UP:
				logRecord += "up";
				break;
			}
			gameLog.LogAdd(logRecord);

			return;
		}

		//Move
		if (room.GetMap()[moveDirection[currDir].Y][moveDirection[currDir].X].GetIsSolid() == false) {
			player.SetPos({ moveDirection[currDir].X, moveDirection[currDir].Y });

			string logRecord = "Move -> ";
			switch (currDir) {
			case LEFT:
				logRecord += "left";
				break;
			case RIGHT:
				logRecord += "right";
				break;
			case DOWN:
				logRecord += "down";
				break;
			case UP:
				logRecord += "up";
				break;
			}
			gameLog.LogAdd(logRecord);

			return;
		}
		else {
			gameLog.LogAdd("Move -> solid obj");
			PrintCurrState();
			goto INVALID_TURN_REPEAT_TURN;
		}
	}

	//UI
	switch (turn) {
	case ' ':
		//ObserverMode();
		gameLog.LogAdd("Set new cam pos");
		camPos = player.GetPos();
		PrintCurrState();
	goto UI_TURN;
	case VK_ESCAPE:
		gameLog.LogAdd("Open menu");
		InGameMenu();
		if (isRunning == 0)
			return;
		if (mainMenuBack == 1)
			return;
	goto UI_TURN;
	}

	//Other
	//Wait
	if (turn == 'c') {
		gameLog.LogAdd("Wait");
		return;
	}

	gameLog.LogAdd("Invalid turn");
	PrintCurrState();
	goto INVALID_TURN_REPEAT_TURN;
}

void GAME::PrintCurrState() {	
	//Map
	OutputAddVisibleMap();

	uchar ii, jj;
	//Skills Key
	for (jj = 1; jj <= 3; ++jj) {
		for (ii = 10; ii < output.GetScreenSizex(); ++ii) {
			if (ii % 5 != 0 || ii == 10) {
				output[output.GetScreenSizey() - jj][ii].SetSymbol(' ');
				output[output.GetScreenSizey() - jj][ii].SetStyle({ outputStyle::color::Black,  outputStyle::color::DarkGray });
			}
			else {
				output[output.GetScreenSizey() - jj][ii].SetSymbol('|');
				output[output.GetScreenSizey() - jj][ii].SetStyle({ outputStyle::color::Black,  outputStyle::color::DarkGray });
			}
		}
	}

	//Menu key
	for (jj = 3; jj < output.GetScreenSizey(); ++jj) {
		for (ii = 0; ii < 10; ++ii) {
			output[jj][ii].SetSymbol(' ');
			output[jj][ii].SetStyle({ outputStyle::color::Black,  outputStyle::color::LightCyan });
		}
	}


	OutputAddBars();

	OutputAddLog();
	
	output.Print();
}

void GAME::ObserverMode() {
	while(1){
		int turn = GetInput();
	
		if (turn == ' ') {
			camPos = player.GetPos();
			return;
		}

		COORD moveDirection[4] = {
			{ camPos.X - 1 , camPos.Y },
		{ camPos.X + 1 , camPos.Y },
		{ camPos.X , camPos.Y + 1 },
		{ camPos.X , camPos.Y - 1 }
		};
		direction currDir = (
			turn == VK_LEFT ? direction::LEFT :
			(turn == VK_RIGHT ? direction::RIGHT :
			(turn == VK_DOWN ? direction::DOWN :
			(turn == VK_UP ? direction::UP :
			(turn == 'a' ? direction::LEFT :
			(turn == 'd' ? direction::RIGHT :
			(turn == 's' ? direction::DOWN :
			(turn == 'w' ? direction::UP :
			direction::NONE_DIR
			))))))));

		if (currDir != direction::NONE_DIR) {
			camPos = moveDirection[currDir];
		}

		PrintCurrState();
	}
}

int GAME::MainMenu() {
	mainMenuBack = 0;
	COORD menuStart = { output.GetScreenSizex() / 2 - 15 , output.GetScreenSizey() / 2 - 10 },
		menuEnd = { output.GetScreenSizex() / 2 + 15, output.GetScreenSizey() / 2 + 10 };
	InitMenuFrame(menuStart, menuEnd);

	char menuPos = 0;
	const char * menu[] = {
		"New Game",
		"Load Game",
		"Settings",
		"Exit"
	};

	do {
		for (uchar i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i) {
			for (uchar j = 0; j < strlen(menu[i]); ++j) {
				if (menuPos != i) {
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetSymbol(menu[i][j]);
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetStyle({ outputStyle::color::White, outputStyle::color::Blue });
				}
				else {
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetSymbol(menu[i][j]);
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetStyle({ outputStyle::color::Yellow, outputStyle::color::Blue });
				}
			}
		}

		output.Print();

		int in = WaitForInput();
		if (in == 'w')
			in = VK_UP;
		else if (in == 'a')
			in = VK_LEFT;
		else if (in == 's')
			in = VK_DOWN;
		else if (in == 'd')
			in = VK_RIGHT;
		else if (in == ' ')
			in = VK_RETURN;

		switch (in) {
		case VK_UP:
			--menuPos;
			break;
		case VK_DOWN:
			++menuPos;
			break;
		case VK_ESCAPE:
		return 0;
		case VK_RETURN:
		VK_RETURN_CLICK:
			switch (menuPos) {
			case 3: //Exit
				isRunning = 0;
				return 0;
			case 2: //Settings
				SettingsMenu();
				break;
			case 1: //Load game
				break;
			case 0: //New game
				return 1;
			}
			break;
		case FROM_LEFT_1ST_BUTTON_PRESSED:
		{
			COORD clickPos = settings.GetClickPos();
			if (clickPos.Y == menuStart.Y && clickPos.X == menuEnd.X) {
				return 0;
			}
			for (uchar i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i) {
				for (uchar j = 0; j < strlen(menu[i]); ++j) {
					if (
						clickPos.Y == i + menuStart.Y + 2 &&
						clickPos.X == j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2
						) {
						menuPos = i;
						goto VK_RETURN_CLICK;
					}
				}
			}
		}
		break;
		}
		if (menuPos == -1)
			menuPos = sizeof(menu) / sizeof(menu[0]) - 1;
		if (menuPos == sizeof(menu) / sizeof(menu[0]))
			menuPos = 0;

	} while (1);
}

bool GAME::GetIsRunning() const {
	return isRunning;
}
bool GAME::GetMainMenuBack() const {
	return mainMenuBack;
}


//------------------------------------------- PRIVATE --------------------------------------------

int GAME::GetInput() {
	int in = input.ReadInput();
	if (INPUT_RIGHT(in))
		return in;
	return ERROR_INPUT_NO_INPUT;
}

int GAME::WaitForInput() {
	while (1) {
		int in = input.ReadInput();
		if (INPUT_RIGHT(in))
			return in;
		Sleep(1);
	}
}

void GAME::InitMenuFrame(COORD menuStart, COORD menuEnd) {
	for (uchar i = menuStart.Y; i <= menuEnd.Y; ++i) {
		for (uchar j = menuStart.X; j <= menuEnd.X; ++j) {
			output[i][j].SetSymbol(' ');
			output[i][j].SetStyle({ outputStyle::color::White, outputStyle::color::Blue });
		}
	}
	output[menuStart.Y][menuEnd.X].SetSymbol('X');
}

void GAME::InGameMenu() {
	COORD menuStart = { output.GetScreenSizex() / 2 - 15 , output.GetScreenSizey() / 2 - 10 },
		menuEnd = { output.GetScreenSizex() / 2 + 15, output.GetScreenSizey() / 2 + 10 };
	InitMenuFrame(menuStart, menuEnd);

	char menuPos = 0;
	const char * menu[] = {
		"Load Game",
		"Save Game",
		"Settings",
		"Return",
		"Main Menu",
		"Exit"
	};

	do {	
		for (uchar i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i) {
			for (uchar j = 0; j < strlen(menu[i]); ++j) {
				if (menuPos != i) {
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetSymbol(menu[i][j]);
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetStyle({ outputStyle::color::White, outputStyle::color::Blue });
				}
				else {
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetSymbol(menu[i][j]);
					output[i + menuStart.Y + 2][j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2].SetStyle({ outputStyle::color::Yellow, outputStyle::color::Blue });
				}
			}
		}

		output.Print();

		int in = WaitForInput();

		if (INPUT_RIGHT(in)) {
			if (in == 'w')
				in = VK_UP;
			else if (in == 'a')
				in = VK_LEFT;
			else if (in == 's')
				in = VK_DOWN;
			else if (in == 'd')
				in = VK_RIGHT;
			else if (in == ' ')
				in = VK_RETURN;

			switch (in) {
			case VK_UP:
				--menuPos;
			break;
			case VK_DOWN:
				++menuPos;
			break;
			case VK_ESCAPE:
				PrintCurrState();
			return;
			case VK_RETURN:
			VK_RETURN_CLICK:
				switch (menuPos) {
				case 5: //Exit
					isRunning = 0;
				return;
				case 4: //Main Menu
					mainMenuBack = 1;
					output.ClearArr();
				return;
				case 3: //Return
					PrintCurrState();
					return;
				case 2: //Settings
					SettingsMenu();
					LogInit();
				break;
				case 1: //Save
				break;
				case 0: //Load
				break;
				}
			break;
			case FROM_LEFT_1ST_BUTTON_PRESSED:
			{
				COORD clickPos = settings.GetClickPos();
				if (clickPos.Y == menuStart.Y && clickPos.X == menuEnd.X) {
					PrintCurrState();
					return;
				}
				for (uchar i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i) {
					for (uchar j = 0; j < strlen(menu[i]); ++j) {
						if (
							clickPos.Y == i + menuStart.Y + 2 &&
							clickPos.X == j + menuStart.X + (menuEnd.X - menuStart.X) / 2 - strlen(menu[i]) / 2
							) {
							menuPos = i;
							goto VK_RETURN_CLICK;
						}
					}
				}
			}
			break;
			}
		}
		if (menuPos == -1)
			menuPos = sizeof(menu) / sizeof(menu[0]) - 1;
		if (menuPos == sizeof(menu) / sizeof(menu[0]))
			menuPos = 0;

	} while (1);
}

void GAME::SettingsMenu() {
	COORD menuStart = { output.GetScreenSizex() / 2 - 15 , output.GetScreenSizey() / 2 - 10 },
		menuEnd = { output.GetScreenSizex() / 2 + 15, output.GetScreenSizey() / 2 + 10 };
	InitMenuFrame(menuStart, menuEnd);

	char menuPos = 0;
	const char * menu[] = {
		"Log Size",
		"Screen Move type",
		"Exit"
	};

	int currState[sizeof(menu) / sizeof(menu[0]) - 1];
	currState[0] = gameLog.GetLogType();
	currState[1] = settings.GetScreenMoveType();
	string menuState[2];

	do {
		if (currState[0] == LOG_GAME::LOG_TYPE::Log_None)
			menuState[0] = "None";
		else if (currState[0] == LOG_GAME::LOG_TYPE::Log_Small)
			menuState[0] = "Small";
		else if (currState[0] == LOG_GAME::LOG_TYPE::Log_Big)
			menuState[0] = "Big";

		if (currState[1] == _settingsGame::SCREEN_MOVE_TYPE::fast)
			menuState[1] = "Fast";
		else if (currState[1] == _settingsGame::SCREEN_MOVE_TYPE::slow)
			menuState[1] = "Slow";

		for (uchar i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i) {
			for (uchar j = 0; j < strlen(menu[i]); ++j) {
				if (menuPos != i) {
					output[i + menuStart.Y + 2][j + menuStart.X + 2].SetSymbol(menu[i][j]);
					output[i + menuStart.Y + 2][j + menuStart.X + 2].SetStyle({ outputStyle::color::White, outputStyle::color::Blue });
				}
				else {
					output[i + menuStart.Y + 2][j + menuStart.X + 2].SetSymbol(menu[i][j]);
					output[i + menuStart.Y + 2][j + menuStart.X + 2].SetStyle({ outputStyle::color::Yellow, outputStyle::color::Blue });
				}
			}
		}

		for (uchar i = 0; i < sizeof(menuState) / sizeof(menuState[0]); ++i) {
			for (short j = menuState[i].length() - 1; j >= 0; --j) {
				if (menuPos != i) {
					output[i + menuStart.Y + 2][j + menuEnd.X - menuState[i].length() - 3].SetSymbol(menuState[i][j]);
					output[i + menuStart.Y + 2][j + menuEnd.X - menuState[i].length() - 3].SetStyle({ outputStyle::color::White, outputStyle::color::Blue });
				}
				else {
					output[i + menuStart.Y + 2][j + menuEnd.X - menuState[i].length() - 3].SetSymbol(menuState[i][j]);
					output[i + menuStart.Y + 2][j + menuEnd.X - menuState[i].length() - 3].SetStyle({ outputStyle::color::Yellow, outputStyle::color::Blue });
				}
			}
			if (menuPos == i) {
				output[i + menuStart.Y + 2][menuEnd.X - menuState[i].length() - 4].SetSymbol('<');
				output[i + menuStart.Y + 2][menuEnd.X - 3].SetSymbol('>');
				output[i + menuStart.Y + 2][menuEnd.X - menuState[i].length() - 4].SetStyle({ outputStyle::color::LightGreen, outputStyle::color::Blue });
				output[i + menuStart.Y + 2][menuEnd.X - 3].SetStyle({ outputStyle::color::LightGreen, outputStyle::color::Blue });
			}
			else {
				output[i + menuStart.Y + 2][menuEnd.X - menuState[i].length() - 4].SetSymbol(' ');
				output[i + menuStart.Y + 2][menuEnd.X - 3].SetSymbol(' ');
			}
		}

		output.Print();

		int in = WaitForInput();

		if (INPUT_RIGHT(in)) {
			if (in == 'w')
				in = VK_UP;
			else if (in == 'a')
				in = VK_LEFT;
			else if (in == 's')
				in = VK_DOWN;
			else if (in == 'd')
				in = VK_RIGHT;
			else if (in == ' ')
				in = VK_RETURN;

			switch (in) {
			case VK_UP:
				--menuPos;
				break;
			case VK_DOWN:
				++menuPos;
				break;
			case VK_LEFT:
				switch (menuPos) {
				case 1: //Screen settings
					--currState[1];
					if (currState[1] <= 0)
						currState[1] = _settingsGame::SCREEN_MOVE_TYPE::slow;
					settings.SetScreenMoveType((_settingsGame::SCREEN_MOVE_TYPE)currState[1]);
				break;
				case 0: //Log settings
				{
					--currState[0];
					if (currState[0] <= 0)
						currState[0] = LOG_GAME::LOG_TYPE::LOG_TYPES_CNT - 1;
					gameLog.SetLogType((LOG_GAME::LOG_TYPE)currState[0]);
				}
				break;
				}
				InitMenuFrame(menuStart, menuEnd);
			break;
			case VK_RIGHT:
				switch (menuPos) {
				case 1: //Screen settings
					++currState[1];
					if (currState[1] > _settingsGame::SCREEN_MOVE_TYPE::slow)
						currState[1] = _settingsGame::SCREEN_MOVE_TYPE::fast;
					settings.SetScreenMoveType((_settingsGame::SCREEN_MOVE_TYPE)currState[1]);
					break;
				case 0: //Log settings
				{
					++currState[0];
					if (currState[0] >= LOG_GAME::LOG_TYPE::LOG_TYPES_CNT)
						currState[0] = LOG_GAME::LOG_TYPE::Log_Big;
					gameLog.SetLogType((LOG_GAME::LOG_TYPE)currState[0]);
				}
				break;
				}
				InitMenuFrame(menuStart, menuEnd);
			break;
			case VK_ESCAPE:
				InitMenuFrame(menuStart, menuEnd);
				output.Print();
				return;
			case VK_RETURN:
			VK_RETURN_CLICK:
				switch (menuPos) {
				case sizeof(menu) / sizeof(menu[0]) - 1 : //Exit
					InitMenuFrame(menuStart, menuEnd);
					output.Print();
				return;
				}
				break;
			case FROM_LEFT_1ST_BUTTON_PRESSED:
			{
				COORD clickPos = settings.GetClickPos();
				if (clickPos.Y == menuStart.Y && clickPos.X == menuEnd.X) {
					InitMenuFrame(menuStart, menuEnd);
					output.Print();
					return;
				}
			}
			break;
			}
		}
		if (menuPos == -1)
			menuPos = sizeof(menu) / sizeof(menu[0]) - 1;
		if (menuPos == sizeof(menu) / sizeof(menu[0]))
			menuPos = 0;

	} while (1);
}

void GAME::OutputAddVisibleMap() {
	COORD startPos, endPos, playerPos;
	playerPos = player.GetPos();
	dungeonMap &currMap = room.GetDisplayInfo();
	RecalcCamPos(startPos, endPos);

	uchar outputPosX, outputPosY;
	outputPosX = outputPosY = 0;
	for (usint i = startPos.Y; i < endPos.Y; ++i) {
		for (usint j = startPos.X; j < endPos.X; ++j) {
			if ( LOVAlgoritm(player.GetPos(), { (short)j, (short)i }) ) {	
				output[outputPosY][outputPosX].SetSymbol(currMap[i][j].GetDisplaySymbol());
				HightlightSymbol(currMap, { (short)j, (short)i }, { outputPosX, outputPosY });
				if (!room.isViewedBefore[i][j])
					room.isViewedBefore[i][j] = 1;	
			}
			else {
				if (room.isViewedBefore[i][j]) {
					output[outputPosY][outputPosX].SetSymbol(currMap[i][j].GetBasicSymbol());
					output[outputPosY][outputPosX].SetStyle(currMap[i][j].GetBasicColor());
				}
				else {
					output[outputPosY][outputPosX].SetSymbol(' ');
					output[outputPosY][outputPosX].SetStyle({});
				}
			}
			++outputPosX;
		}
		++outputPosY;
		outputPosX = 0;
	}
}

void GAME::RecalcCamPos(COORD &startPos,COORD &endPos) {
	COORD playerPos, newCamPos;
	playerPos = player.GetPos();
	newCamPos = player.GetPos();

	if (newCamPos.X - camPos.X == output.GetScreenSizex() / 2 - (logEnd.X - logStart.X + 7)) {
		if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::fast)
			camPos.X = newCamPos.X;
		else if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::slow)
			++camPos.X;
	}
	if (newCamPos.X - camPos.X == -(output.GetScreenSizex() / 2) + 20) {
		if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::fast)
			camPos.X = newCamPos.X;
		else if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::slow)
			--camPos.X;
	}

	if (newCamPos.Y - camPos.Y == output.GetScreenSizey() / 2 - 5) {
		if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::fast)
			camPos.Y = newCamPos.Y;
		else if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::slow)
			++camPos.Y;
	}
	if (newCamPos.Y - camPos.Y == -(output.GetScreenSizey() / 2) + 3) {
		if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::fast)
			camPos.Y = newCamPos.Y;
		else if (settings.GetScreenMoveType() == _settingsGame::SCREEN_MOVE_TYPE::slow)
			--camPos.Y;
	}

	startPos.X = camPos.X - round(output.GetScreenSizex() * 1. / 2);
	startPos.Y = camPos.Y - round(output.GetScreenSizey() * 1. / 2);

	endPos.X = camPos.X + (output.GetScreenSizex() / 2);
	endPos.Y = camPos.Y + (output.GetScreenSizey() / 2);

	if (startPos.X < 0) {
		endPos.X += abs(startPos.X);
		startPos.X = 0;
	}
	if (startPos.Y < 0) {
		endPos.Y += abs(startPos.Y);
		startPos.Y = 0;
	}
	if (endPos.X > room.GetSizex()) {
		startPos.X -= (endPos.X - room.GetSizex());
		endPos.X = room.GetSizex();
	}
	if (endPos.Y > room.GetSizey()) {
		startPos.Y -= (endPos.Y - room.GetSizey());
		endPos.Y = room.GetSizey();
	}
}

bool GAME::LOVAlgoritm(COORD p1, COORD p2) {
	if (pow(p2.X - p1.X, 2) + pow(p2.Y - p1.Y, 2) <= pow(player.lengthOfView.GetCurr(), 2))
		return 1;

	if(abs(p1.X - p2.X) <= 1 && abs(p1.Y - p2.Y) <= 1)
		return 1;

	/*short  deltaX = p1.X - p2.X,
		   deltaY = p1.Y - p2.Y;
	double stepX  = deltaY ? deltaX / deltaY : 0,
		   stepY  = deltaX ? deltaY / deltaX : 0;

	double currX = p1.X, currY = p1.Y;
	int depth = 10;
	while(1){
		if (room.GetDisplayInfo()[(int)round(currY)][(int)round(currX)].GetIsLightSolid())
			return 0;
		currX += stepX;
		currY += stepY;
		if (currX == p2.X && currY == p2.Y)
			return 0;

		--depth;
		if (!depth)
			break;
	}*/

	return 0;
}

void GAME::HightlightSymbol(dungeonMap &currMap, COORD mapPos, COORD outputPos) {
	if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Green)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::LightGreen, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::DarkGray)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::LightGray, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Red)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::LightRed, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Brown)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::Yellow, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Blue)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::LightBlue, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Magenta)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::LightMagenta, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Cyan)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::LightCyan, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::LightGray)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::White, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else if (currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetFore() == outputStyle::color::Black)
		output[outputPos.Y][outputPos.X].SetStyle({ outputStyle::color::DarkGray, currMap[mapPos.Y][mapPos.X].GetDisplayColor().GetBack() });
	else
		output[outputPos.Y][outputPos.X].SetStyle(currMap[mapPos.Y][mapPos.X].GetDisplayColor());
}

void GAME::OutputAddBars() {
	screenObj* bar1 = player.GetHPBar(30);
	screenObj* bar2 = player.GetMPBar(30);
	screenObj* bar3 = player.GetStaminaBar(30);
	for (uchar i = 0; i < 30; ++i) {
		output[0][i] = bar1[i];
		output[1][i] = bar2[i];
		output[2][i] = bar3[i];
	}
	delete[] bar1;
	delete[] bar2;
	delete[] bar3;
}

void GAME::LogInit() {
	//Log init
	uchar logWidth, logHeight;

	if (gameLog.GetLogType() == LOG_GAME::LOG_TYPE::Log_None) {
		logWidth = logHeight = 0;
	}
	else if (gameLog.GetLogType() == LOG_GAME::LOG_TYPE::Log_Small) {
		logWidth = 20;
		logHeight = output.GetScreenSizey() / 3;
	}
	else if (gameLog.GetLogType() == LOG_GAME::LOG_TYPE::Log_Big) {
		logWidth = 20;
		logHeight = output.GetScreenSizey();
	}
	logStart = { output.GetScreenSizex() - logWidth, output.GetScreenSizey() - logHeight };
	logEnd = { output.GetScreenSizex() - 1, output.GetScreenSizey() - 1 };

	++logStart.X;
	++logStart.Y;
	--logEnd.X;
	--logEnd.Y;
}

void GAME::OutputAddLog(){
	for (uchar i = logStart.Y - 1; i <= logEnd.Y + 1; ++i) {
		for (uchar j = logStart.X - 1; j <= logEnd.X + 1; ++j) {
			if (i == logEnd.Y + 1) {
				output[i][j].SetSymbol('_');
				output[i][j].SetStyle({ outputStyle::color::White,  outputStyle::color::Black });
			}
			else if (i == logStart.Y - 1) {
				output[i][j].SetSymbol('_');
				output[i][j].SetStyle({ outputStyle::color::White,  outputStyle::color::Black });
			}
			else if (i != logStart.X - 1 && i != logEnd.X + 1) {
				output[i][j].SetSymbol(' ');
				output[i][j].SetStyle({ outputStyle::color::DarkGray,  outputStyle::color::Black });
			}
		}
		if (i != logEnd.Y + 1 && i != logStart.Y - 1) {
			output[i][logStart.X - 1].SetSymbol('|');
			output[i][logEnd.X + 1].SetSymbol('|');
			output[i][logStart.X - 1].SetStyle({ outputStyle::color::White,  outputStyle::color::Black });
			output[i][logEnd.X + 1].SetStyle({ outputStyle::color::White,  outputStyle::color::Black });
		}
	}

	uchar currPosx;
	uchar currPosy = logStart.Y;
	uchar currLogNote = 0;
	while (currPosy < logEnd.Y) {
		string curr = gameLog.LogGet(currLogNote++);
		currPosx = logStart.X;

		for (usint i = 0; curr[i] != '\0'; ++i) {
			if (curr[i] != '\n') {
				//ўоб не оставл¤ти по 1-2 букви
				if ((currPosx == logEnd.X || currPosx == logEnd.X - 1 || currPosx == logEnd.X - 2) && curr[i - 1] == ' ' && curr[i] != ' ') {
					currPosx = logStart.X;
					++currPosy;
					if (currPosy < logEnd.Y) {
						output[currPosy][currPosx++].SetSymbol(' ');
						output[currPosy][currPosx++].SetSymbol(' ');
					}
				}
				//ўоб оставити перенос 
				else if (currPosx == logEnd.X - 1 && curr[i - 1] != ' ' && curr[i] != ' ' && (curr[i + 1] != ' ' && curr[i + 1] != 0)) {
					if (currLogNote == 1) {
						output[currPosy][currPosx].SetStyle({ outputStyle::color::White,  outputStyle::color::Black });
						output[currPosy][currPosx].SetSymbol('-');
					}
					else {
						output[currPosy][currPosx].SetStyle({ outputStyle::color::DarkGray,  outputStyle::color::Black });
						output[currPosy][currPosx].SetSymbol('-');
					}
					currPosx = logStart.X;
					++currPosy;
					if (currPosy < logEnd.Y) {
						output[currPosy][currPosx++].SetSymbol(' ');
						output[currPosy][currPosx++].SetSymbol(' ');
					}
				}
				//ўоб не вийти за меж≥
				else if (currPosx == logEnd.X + 1) {
					currPosx = logStart.X;
					++currPosy;
					if (currPosy < logEnd.Y) {
						output[currPosy][currPosx++].SetSymbol(' ');
						output[currPosy][currPosx++].SetSymbol(' ');
					}
				}

				if (currPosy < logEnd.Y) {
					if (currLogNote == 1) {
						output[currPosy][currPosx].SetStyle({ outputStyle::color::White,  outputStyle::color::Black });
						output[currPosy][currPosx++].SetSymbol(curr[i]);
					}
					else {
						output[currPosy][currPosx].SetStyle({ outputStyle::color::DarkGray,  outputStyle::color::Black });
						output[currPosy][currPosx++].SetSymbol(curr[i]);
					}
				}
				
			}
			else {
				++currPosy;
			}
		}

		++currPosy;
	}
}
