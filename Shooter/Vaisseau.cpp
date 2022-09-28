#include "Vaisseau.h"
#include "Constants.h"

Vaisseau::Vaisseau(float xP, float yP, float rotationP) :
	Sprite("assets/vaisseau.png", xP, yP, rotationP, true),
	vx{0.f},
	vy{0.f}
{
}

void Vaisseau::Load() {
	Sprite::Load();
	width = GetRectangle().width;
	height = GetRectangle().height;
}

Tir* Vaisseau::Tirer()
{
	Tir* tir = new Tir(x + width, y);
	//Tir tir{ x + width, y };
	tir->Load();
	return tir;
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

	if (x <= width/2) {
		x = width / 2;
	}
	else if (x >= Constants::SCREEN_WIDTH - width / 2) {
		x = Constants::SCREEN_WIDTH - width / 2;
	}
	else if (y <= height / 2) {
		y = height / 2;
	}
	else if (y > Constants::SCREEN_HEIGHT - height / 2) {
		y = Constants::SCREEN_HEIGHT - height / 2;
	}
}
