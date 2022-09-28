#include "Vaisseau.h"
#include "Constants.h"

Vaisseau::Vaisseau(float xP, float yP, float rotationP) :
	Sprite("assets/vaisseau.png", xP, yP, rotationP, true),
	vx{0.f},
	vy{0.f}
{
}

void Vaisseau::Update(float dt)
{
	if (IsKeyDown(KEY_UP)) {
		vy -= Constants::ACCELERATION * dt;
	}
	else if (IsKeyDown(KEY_DOWN)) {
		vy += Constants::ACCELERATION * dt;
	}

	if (IsKeyDown(KEY_LEFT)) {
		vx -= Constants::ACCELERATION * dt;
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		vx += Constants::ACCELERATION * dt;
	}

	if (vx > Constants::MAX_VX) {
		vx = Constants::MAX_VX;
	}
	if (vy > Constants::MAX_VY) {
		vy = Constants::MAX_VY;
	}

	vx *= Constants::DECELERATION;
	vy *= Constants::DECELERATION;

	x += vx;
	y += vy;
}
