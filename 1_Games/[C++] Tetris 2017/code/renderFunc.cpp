#include "preCompiled.h"
#include "renderFunc.h"

void RenderGame() {
	//static bool firstPrint = true;
	if (game != nullptr) {
		hgeQuad *back;
		//if (firstPrint) {
		//	firstPrint = false;
			//Background
			back = game->GetSceneBackground();
			if (back != nullptr)
				hge->Gfx_RenderQuad(back);
		//}

		//Background frame
		back = game->GetBlocksBackground();
		if (back != nullptr)
			hge->Gfx_RenderQuad(back);
		
		//Background info
		gameInfo->PrintBackGround();
		
		//Blocks
		back = game->GetBlackBlock();
		POINT size = game->GetSize();
		bool **mask = game->GetPrintMask();
		hgeQuad **field = game->GetField();
		for (int i = 0; i < size.y; ++i) {
			for (int j = 0; j < size.x; ++j)
				if (mask[i][j])
					hge->Gfx_RenderQuad(&(field[i][j]));
				else {
					for (char k = 0; k < 4; ++k) {
						back->v[k].x = field[i][j].v[k].x;
						back->v[k].y = field[i][j].v[k].y;
					}
					hge->Gfx_RenderQuad(back);
				}
		}

		//Fall figure
		tetrisFigure *figure = game->GetFallingFigure();
		if (figure != nullptr) {
			auto quads = figure->GetQuads();
			mask = figure->GetMask();
			for (int i = 0; i < tetrisFigure::MaxSize; ++i)
				for (int j = 0; j < tetrisFigure::MaxSize; ++j)
					if (mask[i][j])
						hge->Gfx_RenderQuad(&(quads[i][j]));
		}

		//Next figure
		figure = game->GetNextFigure();
		if (figure != nullptr) {
			auto quads = figure->GetQuads();
			mask = figure->GetMask();
			for (int i = 0; i < tetrisFigure::MaxSize; ++i)
				for (int j = 0; j < tetrisFigure::MaxSize; ++j)
					if (mask[i][j]) {
						for (int k = 0; k < 4; ++k) {
							quads[i][j].v[k].x += game->fieldSize.x * game->boxSize.x + 20;
							quads[i][j].v[k].y += 4 * game->boxSize.y + 95;
						}
						hge->Gfx_RenderQuad(&(quads[i][j]));
						for (int k = 0; k < 4; ++k) {
							quads[i][j].v[k].x -= game->fieldSize.x * game->boxSize.x + 20;
							quads[i][j].v[k].y -= 4 * game->boxSize.y + 95;
						}
					}
		}

		game->RenderButtons();
	}
}

void RenderGameInfo() {
	if (gameInfo != nullptr) {
		gameInfo->PrintScore();
	}
}

void RenderMenu() {
	if (menu != nullptr) {
		auto back = menu->GetMenuQuad();
		if(back != nullptr)
			hge->Gfx_RenderQuad(back);
	}
}

void RenderSettings() {
	menu->GetSettingsMenu()->Render();
}

void RenderCredits() {
	hge->Gfx_RenderQuad(menu->GetCreditsQuad());
}