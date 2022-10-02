#include "Ennemi.h"
#include "Constants.h"
#include <cmath>

Ennemi::Ennemi(float xP, float yP, float rotationP) :
	Vaisseau("assets/ennemi.png", xP, yP, rotationP)
{
	PositionnerHauteur();
}

void Ennemi::Update(float dt)
{
	if (vx > Constants::ENNEMI_MAX_VX) {
		vx -= cos(rotation) * abs(Constants::ENNEMI_VITESSE_X) * dt;
	}
	//vy += sin(rotation) * abs(Constants::ENNEMI_VITESSE_Y) * dt;

	Vaisseau::Update(dt);
}

void Ennemi::PositionnerHauteur()
{
	float numRand = (float)rand() / (float)RAND_MAX;
	y = 16 * (1.f * numRand) + ((Constants::SCREEN_HEIGHT - 32) * numRand);
}
