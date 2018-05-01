#include "precompiledHeaders.h"
#include "GAME.h"


GAME::GAME(uchar screenSizex, uchar screenSizey) : output(screenSizex, screenSizey), player(&output), score(&output) {
	isRunning = 1;
	isPause = isAutoShoot = mainMenuBack = 0;
	shootCooldawn = 3;
	currShipHead = currShipSide = currShipCenter = pauseBlink = shootCurrCooldawn = 0;
	RestartDifficult();

	output.SetTitle("BrickGame - Arcade");
	output.MaximizeWindow();
	output.ClearScr();

	currShipColor = outputStyle::color::LightGreen;
	ChangeShip();

	gameMode = BasicEnemy::ClearReturn::MenuLevel;
	MenuLevelHelp();
	currLevel = new level(&player, BasicEnemy::CreateEnemy(gameMode, &output), &output, &score);
	
	ScreenSceneInit();
	score.Set(0);
}

GAME::~GAME(){
	output.BeforeExit();
}

void GAME::MainLoop() {
	DoPlayerTurn();

	if (isPause) {
		BlickPause();
		player.Print();
		output.Print();
		Sleep(100);
		return;
	}
	if (isAutoShoot && !shootCurrCooldawn) {
		currLevel->AddBullet(player.Shot());
		shootCurrCooldawn = shootCooldawn;
	}

	currLevel->CalcBullets();
	currLevel->MoveBullets();
	currLevel->EnemyTurn();

	CheckWin();

	ChangeTurnCnt();
	PrintCurrState();
	Sleep(difficult * 4);
}

void GAME::DoPlayerTurn() {
	if (shootCurrCooldawn)
		--shootCurrCooldawn;
	int input = GetInput();
	if (input == ERROR_INPUT_NO_INPUT)
		return;

	switch (input) {
	case VK_ESCAPE:
		exit(EXIT_SUCCESS);
		break;
	case 'a': case VK_LEFT:  case VK_LBUTTON:
		if(!isPause)
			player.Move({ player.GetPos().X - 1, player.GetPos().Y });
		break;
	case 'd': case VK_RIGHT: case VK_RBUTTON:
		if (!isPause)
			player.Move({ player.GetPos().X + 1, player.GetPos().Y });
		break;
	case VK_SPACE:
		if (!isPause)
			if (!shootCurrCooldawn) {
				currLevel->AddBullet(player.Shot());
				shootCurrCooldawn = shootCooldawn;
			}
		break;
	case 'p':
		if (isPause) {
			pauseBlink = isPause = 0;
			string out = "      ";
			for (int i = 0; i < out.length(); ++i)
				output[output.GetScreenSizey() - 2][output.GetScreenSizex() - 9 + i] = out[i];
		}
		else
			isPause = 1;
		break;
	case 'o':
		if (isAutoShoot)
			isAutoShoot = 0;
		else
			isAutoShoot = 1;
		break;
	case 'z':
		++currShipHead;
		if (currShipHead == sizeof(shipHead) / sizeof(shipHead[0]) - 1)
			currShipHead = 0;
		ChangeShip();
		break;
	case 'x':
		currShipSide += 2;
		if (currShipSide >= sizeof(shipSide) / sizeof(shipSide[0]) - 1)
			currShipSide = 0;
		ChangeShip();
		break;
	case 'c':
		++currShipCenter;
		if (currShipCenter == sizeof(shipCenter) / sizeof(shipCenter[0]) - 1)
			currShipCenter = 0;
		ChangeShip();
		break;
	case 'v':
		int icolor = currShipColor + 1;
		if (icolor > 15)
			icolor = 1;
		currShipColor =(outputStyle::color)icolor;
		ChangeShip();
		break;
	}
}

void GAME::PrintCurrState() {	
	currLevel->PrintBullets();
	currLevel->PrintEnemy();
	
	score.Print();
	PrintDifficult();

	player.Print();

	output.Print();
}

int GAME::MainMenu() {
	mainMenuBack = 0;
	return 1;
}

bool GAME::GetIsRunning() const {
	return isRunning;
}

bool GAME::GetMainMenuBack() const {
	return mainMenuBack;
}


//------------------------------------------- PRIVATE --------------------------------------------

void GAME::ChangeTurnCnt() {
	++turnCnt;
	if (turnCnt > turnsToNextLvl) {
		--difficult;
		turnsToNextLvl = round(turnsToNextLvl * 1.75);
	}
}

void GAME::RestartDifficult() {
	turnCnt = 0;
	difficult = 10;
	turnsToNextLvl = 750;
}

void GAME::CheckWin() {
	level::WinReturn winState = currLevel->IsWin();
	switch (winState)
	{
	case level::Win_None:
		currLevel->EnemyTurn();
		break;
	case level::Win_Win:
		WinWin();
		score.Change(10);
		delete currLevel;
		currLevel = new level(&player, BasicEnemy::CreateEnemy(gameMode, &output), &output, &score);
		break;
	case level::Win_Lose:
		score.Set(0);
		Lose();
		RestartDifficult();
		MenuLevelHelp();
		gameMode = BasicEnemy::ClearReturn::MenuLevel;
		break;
	case level::Win_MenuStaticFigures:
		gameMode = BasicEnemy::ClearReturn::MenuStaticFigures;
		break;
	case level::Win_MenuEndlessFall:
		gameMode = BasicEnemy::ClearReturn::MenuEndlessFall;
		break;
	case level::Win_MenuAlien:
		gameMode = BasicEnemy::ClearReturn::MenuAlien;
		break;
	case level::Win_MenuClassic:
		gameMode = BasicEnemy::ClearReturn::MenuClassic;
		break;
	}
	if (winState != level::Win_Win && winState != level::Win_None) {
		score.Set(0);
		RestartDifficult();
		ClearField();
		delete currLevel;
		currLevel = new level(&player, BasicEnemy::CreateEnemy(gameMode, &output), &output, &score);
	}
	if(winState != level::Win_Lose &&winState != level::Win_Win && winState != level::Win_None)
		MenuLevelHelpClear();
}

void GAME::BlickPause() {
	if (isPause) {
		++pauseBlink;
		if (pauseBlink < 8) {
			string out = "Paused";
			for (int i = 0; i < out.length(); ++i)
				output[output.GetScreenSizey() - 2][output.GetScreenSizex() - 9 + i] = out[i];
		}
		else {
			if (pauseBlink > 12)
				pauseBlink = 0;
			string out = "      ";
			for (int i = 0; i < out.length(); ++i)
				output[output.GetScreenSizey() - 2][output.GetScreenSizex() - 9 + i] = out[i];
		}
	}
}

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

void GAME::ScreenSceneInit() {
	for (int i = 0; i < output.GetScreenSizex(); ++i) {
		output[0][i] = '#';
		output[output.GetScreenSizey() - 1][i] = '#';
		if(i >= output.GetScreenSizex() - 20) 
			output[15][i] = '#';
	}
	for (int i = 0; i < output.GetScreenSizey(); ++i) {
		output[i][0] = '#';
		output[i][output.GetScreenSizex() - 1] = '#';
		output[i][output.GetScreenSizex() - 21] = '#';
	}
	
	string help = " [ad] - move \n arrows - move \n space - shoot \n p - pause \n o - autoshoot \n zxc - change ship \n v - change ship \n ESC - exit";
	for (uchar i = 0, currLine = 0, currPos = 0; i < help.length(); ++i) {
		if (help[i] != '\n') 
			output[17 + currLine][output.GetScreenSizex() - 20 + currPos++] = help[i];
		else {
			++currLine;
			currPos = 0;
		}
	}
}

void GAME::PrintDifficult() {
	string out = "Difficult: ";
	char tmp[32];
	itoa(11 - difficult, tmp, 10);
	out += tmp;
	while (out.length() <= 15)
		out += "   ";
	for (int i = 0; i < out.length(); ++i)
		output[5][output.GetScreenSizex() - 19 + i] = out[i];

//	out = "Turn: ";
//	itoa(turnCnt, tmp, 10);
//	out += tmp;
//	while (out.length() <= 15)
//		out += "   ";
//	for (int i = 0; i < out.length(); ++i)
//		output[6][output.GetScreenSizex() - 19 + i] = out[i];
}

void GAME::ClearField() {
	
	for (int i = 1; i < output.GetScreenSizey() - 1; ++i) {
		for (int j = 1; j < output.GetScreenSizex() - 21; ++j) {
			output[i][j] = 0;
		}
	}
}

void GAME::WinWin() {
	string out = "Win Win!";
	for (int i = 0; i < out.length(); ++i)
		output[output.GetScreenSizey() - 3][output.GetScreenSizex() - 9 + i] = out[i];
	output.Print();

	for (int i = output.GetScreenSizey() - 2; i > 0 ; --i) {
		for (int j = 1; j < output.GetScreenSizex() - 21; ++j) {
			output[i][j] = '#';
			output.Print();
			//Sleep(2);
		}
		Sleep(2);
	}

	for (int i = output.GetScreenSizey() - 2; i > 0; --i) {
		for (int j = 1; j < output.GetScreenSizex() - 21; ++j) {
			output[i][j] = 0;
		}
	}
	player.Print();
	output.Print();
	Sleep(500);

	for (int i = 0; i < out.length(); ++i)
		output[output.GetScreenSizey() - 3][output.GetScreenSizex() - 9 + i] = 0;
}

void GAME::Lose() {
	string out = "Lose";
	for (int i = 0; i < out.length(); ++i)
		output[output.GetScreenSizey() - 3][output.GetScreenSizex() - 9 + i] = out[i];
	output.Print();

	for (int i = output.GetScreenSizey() - 2; i > 0; --i) {
		for (int j = 1; j < output.GetScreenSizex() - 21; ++j) {
			output[i][j] = '#';
			output.Print();
			//Sleep(2);
		}
		Sleep(2);
	}

	for (int i = output.GetScreenSizey() - 2; i > 0; --i) {
		for (int j = 1; j < output.GetScreenSizex() - 21; ++j) {
			output[i][j] = 0;
		}
	}
	player.Print();
	output.Print();
	Sleep(500);

	for (int i = 0; i < out.length(); ++i)
		output[output.GetScreenSizey() - 3][output.GetScreenSizex() - 9 + i] = 0;
}

void GAME::ChangeShip() {
	screenObj spr[4];
	spr[0].SetSymbol(shipHead[currShipHead]);  // & # $ | !
	spr[1].SetSymbol(shipSide[currShipSide]);  // ( { [ ; : / \ 
	spr[2].SetSymbol(shipCenter[currShipCenter]);  // @ # % $ & _ 
	spr[3].SetSymbol(shipSide[currShipSide + 1]);
	for (int i = 0; i < 4; ++i)
		spr[i].SetStyle({ currShipColor, outputStyle::color::Black });
	player.SetSprite(spr);
}

void GAME::MenuLevelHelp() {
	string help = " Destroy any figure \n  to start game \n Each figure launch \n different game";
	for (uchar i = 0, currLine = 0, currPos = 0; i < help.length(); ++i) {
		if (help[i] != '\n') 
			output[30 + currLine][output.GetScreenSizex() - 20 + currPos++] = help[i];
		else {
			++currLine;
			currPos = 0;
		}
	}
}

void GAME::MenuLevelHelpClear() {
	string help = " Destroy any figure\n  to start game\n Each figure launch\n different game";
	for (uchar i = 0, currLine = 0, currPos = 0; i < help.length(); ++i) {
		if (help[i] != '\n')
			output[30 + currLine][output.GetScreenSizex() - 20 + currPos++] = 0;
		else {
			++currLine;
			currPos = 0;
		}
	}
}

