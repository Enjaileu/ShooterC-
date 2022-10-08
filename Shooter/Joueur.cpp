#include "Joueur.h"
#include "Constants.h"

Joueur::Joueur(float xP, float yP, int viesP):
	Vaisseau("assets/vaisseau.png", xP, yP, 0, viesP)
{
}

void Joueur::Update(float dt)
{
	//deplacement
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

	Vaisseau::Update(dt);

	//gerer la vitesse max
	if (x <= 16) {
		x = 16;
	}
	else if (x >= Constants::SCREEN_WIDTH - 16) {
		x = Constants::SCREEN_WIDTH - 16;
	}
	else if (y <= 16) {
		y = 16;
	}
	else if (y > Constants::SCREEN_HEIGHT - 16) {
		y = Constants::SCREEN_HEIGHT -16;
	}
}
