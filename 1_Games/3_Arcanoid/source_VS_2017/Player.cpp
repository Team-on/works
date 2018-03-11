#include "precompiledHeaders.h"
#include "Player.h"


Player::Player(screenScene *outputScene) {
	output = outputScene;
	pos.Y = output->GetScreenSizey() - 2;
	pos.X = output->GetScreenSizex() / 2;
}

Player::~Player() {

}

void Player::SetSprite(const screenObj *spr) {
	sprite[0] = spr[0];
	sprite[1] = spr[1];
	sprite[2] = spr[2];
	sprite[3] = spr[3];
}

// 0
//123
void
Player::Print() const {
	output->operator[](pos.Y - 1)[pos.X] = sprite[0];
	output->operator[](pos.Y)[pos.X] = sprite[2];
	if(pos.X - 1 > 0)
		output->operator[](pos.Y)[pos.X - 1] = sprite[1];
	if (pos.X + 1 < output->GetScreenSizex() - 21)
		output->operator[](pos.Y)[pos.X + 1] = sprite[3];
}

Bullet* Player::Shot() const {
	Bullet *bullet = new Bullet(output, Bullet::DIRECTION::up, { pos.X, pos.Y - 2 }, {'|', outputStyle::color::LightRed
		, outputStyle::color::Black});

	return bullet;
}

void Player::Move(COORD newPos) {
	output->operator[](pos.Y - 1)[pos.X] = output->operator[](pos.Y)[pos.X] = 0;
	if (pos.X - 1 > 0)
		output->operator[](pos.Y)[pos.X - 1] = 0;
	if (pos.X + 1 < output->GetScreenSizex() - 21)
		output->operator[](pos.Y)[pos.X + 1] = 0;

	if(newPos.X > 0 && newPos.X < output->GetScreenSizex() - 21)
		pos = newPos;
}
