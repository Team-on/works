#include "precompiledHeaders.h"
#include "level.h"


level::level(Player * Player, BasicEnemy *Enemy, screenScene *Output, ScoreKeeper *Score) {
	player = Player;
	enemy = Enemy;
	output = Output;
	score = Score;
}

level::~level() {
	for (auto &i : bullets)
		delete i;
	delete enemy;
}

void level::AddBullet(Bullet * bull) {
	bullets.push_back(bull);
}

void level::MoveBullets() {
	for (auto &i : bullets)
		i->Move();
}

void level::PrintBullets() {
	for (auto &i : bullets)
		i->Print();
}

void level::PrintEnemy() {
	enemy->Print();
}

void level::CalcBullets() {
	enemy->DestroyBlocks(bullets, score);
}

void level::EnemyTurn() {
	enemy->Turn();
}

level::WinReturn level::IsWin() {
	BasicEnemy::ClearReturn rez = enemy->IsClear();
	if (rez == BasicEnemy::ClearReturn::MenuAlien)
		return level::WinReturn::Win_MenuAlien;
	if (rez == BasicEnemy::ClearReturn::MenuClassic)
		return level::WinReturn::Win_MenuClassic;
	if (rez == BasicEnemy::ClearReturn::MenuEndlessFall)
		return level::WinReturn::Win_MenuEndlessFall;
	if (rez == BasicEnemy::ClearReturn::MenuStaticFigures)
		return level::WinReturn::Win_MenuStaticFigures;

	if (rez == BasicEnemy::ClearReturn::AllDestroyed)
		return level::WinReturn::Win_Win;

	if (enemy->LowestBlockPosY() >= output->GetScreenSizey() - 3)
		return level::WinReturn::Win_Lose;
	
	if (rez == BasicEnemy::ClearReturn::SomethingLeft)
		return level::WinReturn::Win_None;
	return Win_None;
}
