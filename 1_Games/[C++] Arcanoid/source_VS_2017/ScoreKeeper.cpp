#include "precompiledHeaders.h"
#include "ScoreKeeper.h"

ScoreKeeper::ScoreKeeper(screenScene *ptr) {
	output = ptr;
}

ScoreKeeper::~ScoreKeeper(){

}

void ScoreKeeper::Print() {
	string out = "Score: ";
	char tmp[32];
	itoa(score, tmp, 10);
	out += tmp;
	while (out.length() <= 15)
		out += "   ";
	for (int i = 0; i < out.length(); ++i)
		output[0][4][output->GetScreenSizex() - 19 + i] = out[i];
}

void ScoreKeeper::Change(llint Score) {
	score += Score;
}

void ScoreKeeper::Set(llint Score) {
	score = Score;
}