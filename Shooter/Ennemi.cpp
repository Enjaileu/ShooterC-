#include "Ennemi.h"
#include "Constants.h"
#include <cmath>

Ennemi::Ennemi(float xP, float yP, float rotationP, CoteEcran entreeP, CoteEcran sortieP, float dureePhasePrincipaleP, int viesP) :
	Vaisseau("assets/ennemi.png", rotationP, entreeP, sortieP, xP, yP, dureePhasePrincipaleP, viesP)
{
	PositionnerHauteur();
}

void Ennemi::UpdatePhasePrincipale(float dt)
{
	Vaisseau::UpdatePhasePrincipale(dt);
	if (vx > Constants::ENNEMI_MAX_VX) {
		vx -= cos(rotation) * abs(Constants::ENNEMI_VITESSE_X);
	}
}

void Ennemi::PositionnerHauteur()
{
	float numRand = (float)rand() / (float)RAND_MAX;
	y = 16 * (1.f * numRand) + ((Constants::SCREEN_HEIGHT - 32) * numRand);
}
