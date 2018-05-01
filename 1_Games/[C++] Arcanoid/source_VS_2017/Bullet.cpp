#include "precompiledHeaders.h"
#include "Bullet.h"


Bullet::Bullet(screenScene *screen, DIRECTION dir, COORD startPos, screenObj spr) {
	output = screen;
	direction = dir;
	pos = startPos;
	sprite = spr;
}

Bullet::~Bullet() {

}

void Bullet::SetUnused(bool unUsed) {
	if(unUsed)
		direction = DESTROY;
}

bool Bullet::GetUnused() const {
	return direction == DESTROY;
}

void Bullet::Move() {
	if (direction != DESTROY) {
		output->operator[](pos.Y)[pos.X] = 0;
		if (direction == up)
			--pos.Y;
		else if (direction == down)
			++pos.Y;
		if(pos.Y <= 0 || pos.Y >= output->GetScreenSizey())
			direction = DESTROY;
	}
}

void Bullet::Destroy() {
	output->operator[](pos.Y)[pos.X] = 0;
	direction = DESTROY;
	pos.X = pos.Y = -1;
}

void Bullet::Print() const {
	if(direction != DESTROY)
		output->operator[](pos.Y)[pos.X] = sprite;
}
