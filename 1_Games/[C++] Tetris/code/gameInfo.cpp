#include "preCompiled.h"
#include "gameInfo.h"


GameInfo::GameInfo(){
	Reload();

	scoreNumber = new ScoreNumber();
	scoreNumber->Init();
	scorePos = { game->fieldStartPos.x + (game->fieldSize.x + 2) * (game->boxSize.x + game->borderWidth) + 30, 
		game->fieldStartPos.y + game->boxSize.y + game->borderWidth + 48 };

	game->InitBasicQuad();
	background = game->CreateBlock(hgeColor(1, 1, 1, 1), 

		{ game->fieldStartPos.x + (game->fieldSize.x + 1) * (game->boxSize.x + game->borderWidth), 
		game->fieldStartPos.y},

		{ screenSize.x - game->fieldStartPos.x - (game->fieldSize.x + 2) * (game->boxSize.x + game->borderWidth),
		  game->fieldSize.y * (game->boxSize.y + game->borderWidth) }
	);

	background.tex = hge->Texture_Load("infoBackground.png");
}

GameInfo::~GameInfo(){
	delete scoreNumber;
}

void GameInfo::PrintBackGround() {
	hge->Gfx_RenderQuad(&background);
}

void GameInfo::PrintScore() {
	unsigned long long scoreTmp = score;
	char i = 4;
	while (i-- != 0) {
		scoreNumber->PrintNumber({ scorePos.x + i * scoreNumber->w, scorePos.y}, scoreTmp % 10);
		scoreTmp /= 10;
	}
}

void GameInfo::Reload() {
	backPrinted = false;
	score = 0;
}
