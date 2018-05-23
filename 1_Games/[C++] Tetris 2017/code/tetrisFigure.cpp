#include "preCompiled.h"
#include "tetrisFigure.h"
#include "game.h"

bool tetrisFigure::xmlLoaded = false;
int tetrisFigure::MaxSize = 4;
bool *** tetrisFigure::masks = nullptr;
tetrisFigure::TYPE * tetrisFigure::masksTypes = nullptr;
unsigned int tetrisFigure::masksCnt = 0;

tetrisFigure::tetrisFigure(){
	auto color = game->GetRandomNonBlackColor();
	game->InitBasicQuad();

	figure = new hgeQuad*[tetrisFigure::MaxSize];
	isUsed = new bool*[tetrisFigure::MaxSize];
	for (char i = 0; i < tetrisFigure::MaxSize; ++i) {
		figure[i] = new hgeQuad[tetrisFigure::MaxSize];
		isUsed[i] = new bool[tetrisFigure::MaxSize];
		for (char j = 0; j < tetrisFigure::MaxSize; ++j) {
			figure[i][j] = game->CreateBlock(color,
				{ game->boxSize.x * (j + 4) + game->fieldStartPos.x + (j + 4) * game->borderWidth,
				game->boxSize.y * i + game->fieldStartPos.y + i * game->borderWidth },
				{ game->boxSize.x, game->boxSize.y });
			isUsed[i][j] = false;
		}
	}

	FillWithRandFigure(color);
}

tetrisFigure::~tetrisFigure(){
	for (char i = 0; i < tetrisFigure::MaxSize; ++i) {
		delete[] figure[i];
		delete[] isUsed[i];
	}
	delete[] figure;
	delete[] isUsed;
}

void tetrisFigure::Rotate() {
	BasicRotate(isUsed);
}

bool ** tetrisFigure::RotateSample() {
	bool **res = new bool*[tetrisFigure::MaxSize];
	for (char i = 0; i < tetrisFigure::MaxSize; ++i) {
		res[i] = new bool[tetrisFigure::MaxSize];
		for (char j = 0; j < tetrisFigure::MaxSize; ++j) 
			res[i][j] = isUsed[i][j];
	}
	BasicRotate(res);

	return res;
}

void tetrisFigure::BasicRotate(bool **mtx) {
	if (type == O || type == UnRotatable)
		return;

	bool tmp;
	int	MaxSizeAlt = 0;
	for (int i = 0; i < MaxSize; i++) 
		for (int j = 0; j < MaxSize; j++) 
			if (mtx[i][j] && (((i > j) ? i : j) > MaxSizeAlt)) 
					MaxSizeAlt = ((i > j) ? i : j);
	++MaxSizeAlt;

	if (type == I || type == Transportable) {
		for (int i = 0; i < MaxSizeAlt; i++) {
			for (int j = 0; j < i; j++) {
				tmp = mtx[i][j];
				mtx[i][j] = mtx[j][i];
				mtx[j][i] = tmp;
			}
		}
		return;
	}

	for (int i = 0; i < MaxSizeAlt / 2; i++){
		for (int j = i; j < MaxSizeAlt - 1 - i; j++){
			tmp = mtx[i][j];
			mtx[i][j] = mtx[MaxSizeAlt - j - 1][i];
			mtx[MaxSizeAlt - j - 1][i] = mtx[MaxSizeAlt - i - 1][MaxSizeAlt - j - 1];
			mtx[MaxSizeAlt - i - 1][MaxSizeAlt - j - 1] = mtx[j][MaxSizeAlt - i - 1];
			mtx[j][MaxSizeAlt - i - 1] = tmp;
		}
	}
}

void tetrisFigure::MoveLeft() {
	for (char i = 0; i < tetrisFigure::MaxSize; ++i)
		for (char j = 0; j < tetrisFigure::MaxSize; ++j)
			for (char k = 0; k < 4; ++k)
				figure[i][j].v[k].x -= game->boxSize.x + game->borderWidth;
}

void tetrisFigure::MoveRight() {
	for (char i = 0; i < tetrisFigure::MaxSize; ++i)
		for (char j = 0; j < tetrisFigure::MaxSize; ++j)
			for (char k = 0; k < 4; ++k)
				figure[i][j].v[k].x += game->boxSize.x + game->borderWidth;
}

void tetrisFigure::MoveDown() {
	for (char i = 0; i < 4; ++i)
		for (char j = 0; j < 4; ++j)
			for (char k = 0; k < 4; ++k)
				figure[i][j].v[k].y += game->boxSize.y + game->borderWidth;
}

//---------------------------------- Generator -----------------------------------------------

void tetrisFigure::FillWithRandFigure(hgeColor color) {
	if (!xmlLoaded) {
		switch (rand() % 7) {
		case 0:
			FillWithJ(color);
			break;
		case 1:
			FillWithL(color);
			break;
		case 2:
			FillWithO(color);
			break;
		case 3:
			FillWithT(color);
			break;
		case 4:
			FillWithS(color);
			break;
		case 5:
			FillWithZ(color);
			break;
		case 6:
			FillWithI(color);
			break;
		default:
			break;
		}
	}
	else {
		FillWithMaskById(color, rand() % masksCnt);
	}
}

void tetrisFigure::LoadFromXml() {
	TiXmlDocument doc;
	xmlLoaded = doc.LoadFile("figures.xml");
	if (xmlLoaded){
		bool ErrorWhileLoad = false;

		try {
			TiXmlHandle hDoc(&doc);
			TiXmlElement *root;
			root = doc.FirstChildElement();
			if (root) {
				for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
					string elemName = elem->Value();
					if (elemName == "maxSize")
						tetrisFigure::MaxSize = atoi(elem->GetText());
					else if (elemName == "figure")
						++masksCnt;
				}

				masksTypes = new tetrisFigure::TYPE[masksCnt];
				tetrisFigure::masks = new bool**[masksCnt];
				for (unsigned int i = 0; i < masksCnt; ++i) {
					masksTypes[i] = TYPE::TypeOther;
					masks[i] = new bool*[tetrisFigure::MaxSize];
					for (int j = 0; j < MaxSize; ++j)
						masks[i][j] = new bool[tetrisFigure::MaxSize];
				}

				int currMask = 0, currRow, currSumbol;
				for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
					const char * const attribValue = elem->Attribute("type");
					if (attribValue != NULL){
						if (strcmp(attribValue, "Rotatable") == 0)
							masksTypes[currMask] = TYPE::Rotatable;
						else if (strcmp(attribValue, "UnRotatable") == 0)
							masksTypes[currMask] = TYPE::UnRotatable;
						else if (strcmp(attribValue, "Transportable") == 0)
							masksTypes[currMask] = TYPE::Transportable;
					}

					string elemName = elem->Value();
					if (elemName == "figure") {
						currRow = 0;
						for (TiXmlElement* row = elem->FirstChildElement(); row != NULL && currRow < tetrisFigure::MaxSize; row = row->NextSiblingElement()) {
							elemName = row->GetText();
							for (currSumbol = 0; currSumbol < tetrisFigure::MaxSize; ++currSumbol)
								masks[currMask][currRow][currSumbol] = ((elemName[currSumbol] == '@') ? true : false);
							++currRow;
						}
						++currMask;
					}
				}
			}
			else
				ErrorWhileLoad = true;
		}
		catch (exception) {
			ErrorWhileLoad = true;
		}

		if (ErrorWhileLoad)
			xmlLoaded = false;
		doc.Clear();
	}
}

void tetrisFigure::FillWithJ(hgeColor color) {
	SetQuad(color, 0, 0);
	SetQuad(color, 1, 0);
	SetQuad(color, 1, 1);
	SetQuad(color, 1, 2);
	type = J;
}

void tetrisFigure::FillWithL(hgeColor color) {
	SetQuad(color, 0, 2);
	SetQuad(color, 1, 0);
	SetQuad(color, 1, 1);
	SetQuad(color, 1, 2);
	type = L;
}

void tetrisFigure::FillWithO(hgeColor color){
	SetQuad(color, 0, 0);
	SetQuad(color, 0, 1);
	SetQuad(color, 1, 0);
	SetQuad(color, 1, 1);
	type = O;

}

void tetrisFigure::FillWithT(hgeColor color) {
	SetQuad(color, 0, 1);
	SetQuad(color, 1, 0);
	SetQuad(color, 1, 1);
	SetQuad(color, 1, 2);
	type = T;
}

void tetrisFigure::FillWithZ(hgeColor color) {
	SetQuad(color, 0, 0);
	SetQuad(color, 0, 1);
	SetQuad(color, 1, 1);
	SetQuad(color, 1, 2);
	type = Z;
}

void tetrisFigure::FillWithS(hgeColor color) {
	SetQuad(color, 0, 1);
	SetQuad(color, 0, 2);
	SetQuad(color, 1, 0);
	SetQuad(color, 1, 1);
	type = S;
}

void tetrisFigure::FillWithI(hgeColor color) {
	SetQuad(color, 1, 0);
	SetQuad(color, 1, 1);
	SetQuad(color, 1, 2);
	SetQuad(color, 1, 3);
	type = I;
}

void tetrisFigure::FillWithMaskById(hgeColor color, int id) {
	type = masksTypes[id];
	for(int i = 0; i < MaxSize; ++i)
		for (int j = 0; j < MaxSize; ++j)
			if(masks[id][j][i])
			SetQuad(color, j, i);
}

void tetrisFigure::SetQuad(hgeColor color, int idy, int idx) {
	isUsed[idy][idx] = true;
	figure[idy][idx] = game->CreateBlock(color,
		{ game->boxSize.x * (4 + idx) + game->fieldStartPos.x + (4 + idx) * game->borderWidth,
		game->boxSize.y * (0 + idy) + game->fieldStartPos.y + (0 + idy) * game->borderWidth },
		{ game->boxSize.x, game->boxSize.y });
}
