#include "Ennemi.h"
#include "Constants.h"
#include <cmath>

Ennemi::Ennemi(float xP, float yP, float rotationP) :
	Sprite("assets/ennemi.png", xP, yP, rotationP, true),
	vx{ 0.f },
	vy{ 0.f }
{
	PositionnerHauteur();
}

void Ennemi::Update(float dt)
{
	if (vx > Constants::ENNEMI_MAX_VX) {
		vx -= cos(rotation) * abs(Constants::ENNEMI_VITESSE_X) * dt;
	}
	//vy += sin(rotation) * abs(Constants::ENNEMI_VITESSE_Y) * dt;

	x += vx;
}

void Ennemi::PositionnerHauteur()
{
	float numRand = (float)rand() / (float)RAND_MAX;
	//y = numRand * Constants::SCREEN_WIDTH + 16;
	y = 16 * (1.f * numRand) + ((Constants::SCREEN_HEIGHT - 32) * numRand);
}
