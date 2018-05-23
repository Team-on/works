#include "preCompiled.h"
#include "scoreNumber.h"

ScoreNumber::ScoreNumber(){
}


ScoreNumber::~ScoreNumber(){

}

void ScoreNumber::Init() {
	DWORD color = hgeColor(1, 1, 1, 0.85f).GetHWColor();

	for (int i = 0; i < 10; ++i) {
		string path = "number\\";
		path += i + '0';
		path += ".png";
		n[i].tex = hge->Texture_Load(path.c_str());

		n[i].blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;

		n[i].v[0].tx = 0; n[i].v[0].ty = 0;
		n[i].v[1].tx = 1; n[i].v[1].ty = 0;
		n[i].v[2].tx = 1; n[i].v[2].ty = 1;
		n[i].v[3].tx = 0; n[i].v[3].ty = 1;

		for (int j = 0; j < 4; j++) {
			n[i].v[j].z = 0.5f;
			n[i].v[j].col = color;
		}
	}
}

void ScoreNumber::PrintNumber(POINT pos, int i) {
	n[i].v[0].x = (float) pos.x;	 n[i].v[0].y = (float) pos.y;
	n[i].v[1].x = (float) pos.x + w; n[i].v[1].y = (float) pos.y;
	n[i].v[2].x = (float) pos.x + w; n[i].v[2].y = (float) pos.y + h;
	n[i].v[3].x = (float) pos.x;	 n[i].v[3].y = (float) pos.y + h;

	hge->Gfx_RenderQuad(n + i);
}