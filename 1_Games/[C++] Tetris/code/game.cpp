#include "preCompiled.h"
#include "game.h"
#include <fstream>

Game::Game() : buttonsSize(4) {
	isPaused = false;
	isRunning = true;

	borderWidth = 1;
	boxSize.x = boxSize.y = 25;
	fieldSize.x = 10;
	fieldSize.y = 20;
	fieldStartPos.x = (screenSize.x - boxSize.x * fieldSize.x - (fieldSize.x - 1) * borderWidth) / 2;
	fieldStartPos.y = (screenSize.y - boxSize.y * fieldSize.y - (fieldSize.y - 1) * borderWidth) / 2;

	InitBasicQuad();
	blackBlock = new hgeQuad(CreateBlock(hgeColor(0.f, 0.f, 0.f, 0.8f),
		{ 0, 0 },
		{ boxSize.x, boxSize.y }));

	backgroundBlock = new hgeQuad(CreateBlock(hgeColor(1, 1, 1, 1), { fieldStartPos.x - borderWidth * 3, fieldStartPos.y - borderWidth * 3 },
		{ fieldSize.x * boxSize.x + borderWidth * (fieldSize.x - 1) + borderWidth * 6, fieldSize.y * boxSize.y + borderWidth * (fieldSize.y - 1) + borderWidth * 6 }));
	backgroundBlock->tex = hge->Texture_Load("blockBackground.jpg");
	backgroundBlock->v[0].tx = 0; backgroundBlock->v[0].ty = 0;
	backgroundBlock->v[1].tx = 5; backgroundBlock->v[1].ty = 0;
	backgroundBlock->v[2].tx = 5; backgroundBlock->v[2].ty = 5;
	backgroundBlock->v[3].tx = 0; backgroundBlock->v[3].ty = 5;

	backgroundScene = new hgeQuad(CreateBlock(hgeColor(1, 1, 1, 1), {0, 0}, screenSize));
	backgroundScene->tex = hge->Texture_Load("background.jpg");
	backgroundScene->v[0].tx = 0; backgroundScene->v[0].ty = 0;
	backgroundScene->v[1].tx = 1; backgroundScene->v[1].ty = 0;
	backgroundScene->v[2].tx = 1; backgroundScene->v[2].ty = 1;
	backgroundScene->v[3].tx = 0; backgroundScene->v[3].ty = 1;

	field = new hgeQuad*[fieldSize.y];
	fieldFilled = new bool*[fieldSize.y];
	for (char i = 0; i < fieldSize.y; ++i) {
		field[i] = new hgeQuad[fieldSize.x];
		fieldFilled[i] = new bool[fieldSize.x];
		for (char j = 0; j < fieldSize.x; ++j) {
			field[i][j] = CreateBlock(GetRandomNonBlackColor(),
				{ boxSize.x * j + fieldStartPos.x + j * borderWidth, boxSize.y * i + fieldStartPos.y + i * borderWidth },
				{ boxSize.x, boxSize.y });
			fieldFilled[i][j] = false;
		}
	}
	nextFigure = figure = nullptr;

	buttons = new Button*[buttonsSize];
	POINT size{ 177,25 }, startPos{ fieldStartPos.x - size.x - boxSize.x, fieldStartPos.y + 3 * (boxSize.y + borderWidth)};
	void(*func)(void) = nullptr;
	hgeQuad *quad = nullptr;
	auto color = hgeColor(1, 1, 1, 1).GetHWColor();
	HTEXTURE hover = NULL;

	for (char i = 0; i < buttonsSize; ++i) {
		quad = new hgeQuad(_basicQuad);

		if (i == 0) {
			quad->tex = hge->Texture_Load("buttons\\pause.png");
			hover = hge->Texture_Load("buttons\\pause_hover.png");
			func = []() {game->isPaused = !game->isPaused; if(game->isPaused) soundMusic->Stop(); else soundMusic->Play(); };
		}
		else if (i == 1) {
			quad->tex = hge->Texture_Load("buttons\\save.png");
			hover = hge->Texture_Load("buttons\\save_hover.png");
			func = []() {game->Save(); };
		}
		else if (i == 2) {
			quad->tex = hge->Texture_Load("buttons\\load.png");
			hover = hge->Texture_Load("buttons\\load_hover.png");
			func = []() {game->Load(); };
		}
		else if (i == 3) {
			quad->tex = hge->Texture_Load("buttons\\back.png");
			hover = hge->Texture_Load("buttons\\back_hover.png");
			func = []() {game->isRunning = false; soundMusic->Stop(); };
		}

		quad->v[0].x = (float) startPos.x; quad->v[0].y = (float)startPos.y;
		quad->v[1].x = (float) startPos.x + size.x; quad->v[1].y = (float)startPos.y;
		quad->v[2].x = (float)startPos.x + size.x; quad->v[2].y = (float)startPos.y + size.y;
		quad->v[3].x = (float)startPos.x; quad->v[3].y = (float)startPos.y + size.y;

		quad->v[0].col = color;
		quad->v[1].col = color;
		quad->v[2].col = color;
		quad->v[3].col = color;

		buttons[i] = new Button(quad, func, hover);

		startPos.y += size.y * 2;
	}
}

Game::~Game(){
	for (int i = 0; i < game->GetSize().y; ++i)
		for (int j = 0; j < game->GetSize().x; ++j)
			hge->Texture_Free(field[i][j].tex);

	for (char i = 0; i < fieldSize.y; ++i) {
		delete[] field[i];
		delete[] fieldFilled[i];
	}
	delete[] field;
	delete[] fieldFilled;
	delete backgroundBlock;
	delete blackBlock;
}

//----------------------------------------- Save/Load -----------------------------------------

void Game::Save() {
	ofstream fout("save.sav");
	for (char i = 0; i < fieldSize.y; ++i) {
		for (char j = 0; j < fieldSize.x; ++j) {
			fout << (int) fieldFilled[i][j] << ' ';
		}
		fout << endl;
	}
	fout.close();
}

void Game::Load() {
	ifstream fin("save.sav");
	//if (!fin.is_open())
		//return;
	for (char i = 0; i < fieldSize.y; ++i) 
		for (char j = 0; j < fieldSize.x; ++j) 
			fin >> fieldFilled[i][j];
	fin.close();
}

//----------------------------------------- Main loop -----------------------------------------

void Game::Init() {
	nextFigure = CreateNewFallFigure();
	figure = CreateNewFallFigure();
}

bool Game::CheckExit(){
	return !isRunning;
}

bool Game::Loop() {
	if (isPaused)
		return true;

	if(!CheckCollisionWithFloor())
		Fall();
	else {
		soundSound->Play("sounds\\Drop.ogg");
		PassFigureToArr();
		delete figure;
		figure = std::move(nextFigure);
		nextFigure = CreateNewFallFigure();
		DestroyLines();
	}
	if (IsLose()) {
		soundSound->Play("sounds\\GameOver.ogg");
		Sleep(2500);
		return false;
	}
	return true;
}

void Game::Reload() {
	isRunning = true;
	isPaused = false;
	delete nextFigure;
	delete figure;
	for (char i = 0; i < fieldSize.y; ++i) 
		for (char j = 0; j < fieldSize.x; ++j) 
			fieldFilled[i][j] = false;
	Init();
}

bool Game::IsLose() {
	for (int j = 0; j < fieldSize.x; ++j)
		if (fieldFilled[0][j])
			return true;
	return false;
}

void Game::DestroyLines() {
	bool lineFull;
	unsigned short scoreToAdd = 0;
	int combo = 0;
REPEAT_DESTROY:
	for (int i = fieldSize.y - 1; i >= 0; --i) {
		lineFull = true;
		for (int j = 0; j < fieldSize.x; ++j) 
			if (!fieldFilled[i][j])
				lineFull = false;

		if (lineFull) {
			if (!scoreToAdd)
				scoreToAdd = 1;
			else if(scoreToAdd == 1)
				scoreToAdd = 3;
			else
				scoreToAdd *= 2;

			for (int j = 0; j < fieldSize.x; ++j) 
				fieldFilled[i][j] = false;

			int delIndex = i;
			for (int shifhy = delIndex; shifhy > 0 ; --shifhy)
				for (int shifhx = 0; shifhx < fieldSize.x; ++shifhx)
					if (fieldFilled[shifhy - 1][shifhx]) {
						fieldFilled[shifhy - 1][shifhx] = false;
						fieldFilled[shifhy][shifhx] = true;
						field[shifhy][shifhx].tex = field[shifhy - 1][shifhx].tex;
						for (int vi = 0; vi < 4; ++vi)
							field[shifhy][shifhx].v[vi].col = field[shifhy - 1][shifhx].v[vi].col;
					}

			++combo;
			goto REPEAT_DESTROY;
		}
	}
	if (scoreToAdd) {
		gameInfo->AddScore(scoreToAdd);
		difficult->TrySpeedUp(gameInfo->GetScore());

		if(combo == 1)
			soundSound->Play("sounds\\Clear1.ogg");
		else if (combo == 2)
			soundSound->Play("sounds\\Clear2.ogg");
		else if (combo == 3)
			soundSound->Play("sounds\\Clear3.ogg");
		else if (combo == 4)
			soundSound->Play("sounds\\Clear4.ogg");
		else
			soundSound->Play("sounds\\Clear4.ogg");
	}
}

void Game::CheckButtons() {
	for (char i = 0; i < buttonsSize; ++i) 
		buttons[i]->CheckClick();
}

//-----------------------------------------  Fall -----------------------------------------

void Game::Fall(){
	figure->MoveDown();
}

bool Game::CheckCollisionWithFloor() {
	auto fig = figure->GetQuads();
	auto mask = figure->GetMask();
	for (int i = tetrisFigure::MaxSize - 1; i >= 0; --i)
		for (int j = 0; j < tetrisFigure::MaxSize; ++j)
			if (mask[i][j])
				if (fig[i][j].v[0].y == boxSize.y * (fieldSize.y - 1) + fieldStartPos.y + (fieldSize.y - 1) * borderWidth)
					return true;

	for (int i = tetrisFigure::MaxSize - 1; i >= 0; --i)
		for (int j = 0; j < tetrisFigure::MaxSize; ++j)
			if (mask[i][j]) {
				POINT p = ScreenPosToArrPos({ (LONG)fig[i][j].v[0].x, (LONG)fig[i][j].v[0].y });
				if (fieldFilled[p.y + 1][p.x])
					return true;
			}


	return false;
}

bool Game::CheckCollisionLeft() {
	auto fig = figure->GetQuads();
	auto mask = figure->GetMask();
	for (int i = 0; i < tetrisFigure::MaxSize; ++i)
		for (int j = 0; j < tetrisFigure::MaxSize; ++j)
			if (mask[i][j])
				if (fig[i][j].v[0].x == fieldStartPos.x)
					return true;

	for (int i = tetrisFigure::MaxSize - 1; i >= 0; --i)
		for (int j = 0; j < tetrisFigure::MaxSize; ++j)
			if (mask[i][j]) {
				POINT p = ScreenPosToArrPos({ (LONG)fig[i][j].v[0].x, (LONG)fig[i][j].v[0].y });
				if (fieldFilled[p.y][p.x - 1])
					return true;
			}

	return false;
}

bool Game::CheckCollisionRight() {
	auto fig = figure->GetQuads();
	auto mask = figure->GetMask();
	for (int i = 0; i < tetrisFigure::MaxSize; ++i)
		for (int j = tetrisFigure::MaxSize - 1; j >= 0; --j)
			if (mask[i][j])
				if (fig[i][j].v[0].x == field[0][fieldSize.x - 1].v[0].x)
					return true;

	for (int i = tetrisFigure::MaxSize - 1; i >= 0; --i)
		for (int j = 0; j < tetrisFigure::MaxSize; ++j)
			if (mask[i][j]) {
				POINT p = ScreenPosToArrPos({ (LONG)fig[i][j].v[0].x, (LONG)fig[i][j].v[0].y });
				if (fieldFilled[p.y][p.x + 1])
					return true;
			}

	return false;
}

POINT Game::ScreenPosToArrPos(POINT pos) {
	POINT res;
	for (char i = 0; i < fieldSize.y; ++i) {
		for (char j = 0; j < fieldSize.x; ++j) {
			if (pos.x == boxSize.x * j + fieldStartPos.x + j * borderWidth)
				res.x = j;
			if (pos.y == boxSize.y * i + fieldStartPos.y + i * borderWidth)
				res.y = i;
		}
	}
	return res;
}

void Game::PassFigureToArr() {
	if (figure != nullptr) {
		POINT pnt;
		auto quads = figure->GetQuads();
		auto mask = figure->GetMask();
		for (int i = 0; i < tetrisFigure::MaxSize; ++i)
			for (int j = 0; j < tetrisFigure::MaxSize; ++j)
				if (mask[i][j]) {
					pnt = ScreenPosToArrPos({ (LONG)quads[i][j].v[0].x, (LONG)quads[i][j].v[0].y });
					field[pnt.y][pnt.x].tex = quads[i][j].tex;
					for(char k = 0; k < 4; ++k)
						field[pnt.y][pnt.x].v[k].col = quads[i][j].v[k].col;
					fieldFilled[pnt.y][pnt.x] = true;
				}
	}
}

//----------------------------------------- Input -----------------------------------------
void Game::MoveDown() {
	Loop();
}

void Game::MoveLeft() {
	if (!CheckCollisionLeft()) {
		figure->MoveLeft();
		soundSound->Play("sounds\\MoveLR.ogg");
	}
}

void Game::MoveRight() {
	if (!CheckCollisionRight()){
		figure->MoveRight();
		soundSound->Play("sounds\\MoveLR.ogg");
	}
}

void Game::Rotate() {
	if(CanRotate()){
		figure->Rotate();
		soundSound->Play("sounds\\Rotate.ogg");
	}
}

bool Game::CanRotate() {
	auto fig = figure->GetQuads();
	POINT p;
	bool ** maskAfterRotate = figure->RotateSample();

	for (int i = tetrisFigure::MaxSize - 1; i >= 0; --i)
		for (int j = 0; j < tetrisFigure::MaxSize; ++j)
			if (maskAfterRotate[i][j]) {
				p = ScreenPosToArrPos({ (LONG)fig[i][j].v[0].x, (LONG)fig[i][j].v[0].y });
				if (p.y < 0 || p.y >= fieldSize.y || p.x < 0 || p.x >= fieldSize.x || fieldFilled[p.y][p.x]) {
					DeleteMtx(maskAfterRotate, tetrisFigure::MaxSize);
					return false;
				}
			}
	DeleteMtx(maskAfterRotate, tetrisFigure::MaxSize);
	return true;
}

//----------------------------------------- FOR OUTPUT -----------------------------------------
void Game::RenderButtons() {
	for (char i = 0; i < buttonsSize; ++i) 
		buttons[i]->Render();
}

//----------------------------------------- GENERATOR -----------------------------------------

tetrisFigure *Game::CreateNewFallFigure() {
	return new tetrisFigure();
}

//Або текстура буде нормальною, або з 5% шансом синішою(типа маны нехватило)
hgeColor Game::GetRandomNonBlackColor() {
	if(rand() % 20 <= 1)
		return hgeColor(0.50, 0.50, 1, 1);
	return hgeColor(1, 1, 1, 1);
}

void Game::InitBasicQuad() {
	char tmp[5];
	_itoa(rand() % 1085 + 1, tmp, 10);
	string path = "block\\title (";
	path += tmp;
	path += ").png";

	_basicQuad.tex = hge->Texture_Load(path.c_str());

	_basicQuad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;

	_basicQuad.v[0].tx = 0; _basicQuad.v[0].ty = 0;
	_basicQuad.v[1].tx = 1; _basicQuad.v[1].ty = 0;
	_basicQuad.v[2].tx = 1; _basicQuad.v[2].ty = 1;
	_basicQuad.v[3].tx = 0; _basicQuad.v[3].ty = 1;

	for (int i = 0; i < 4; i++)
		_basicQuad.v[i].z = 0.5f;
}

hgeQuad Game::CreateBlock(hgeColor color, POINT start, POINT size) {
	hgeQuad res(_basicQuad);

	for (int i = 0; i < 4; i++)
		res.v[i].col = color.GetHWColor();

	res.v[0].x = (float)start.x; res.v[0].y = (float)start.y;
	res.v[1].x = (float)start.x + size.x; res.v[1].y = (float)start.y;
	res.v[2].x = (float)start.x + size.x; res.v[2].y = (float)start.y + size.y;
	res.v[3].x = (float)start.x; res.v[3].y = (float)start.y + size.y;

	return res;
}
