#include "Joueur.h"
#include "Constants.h"

Joueur::Joueur(float xP, float yP, CoteEcran entreeP, CoteEcran sortieP, int viesP):
	Vaisseau("assets/vaisseau.png", 0, entreeP, sortieP, xP, yP, -1, viesP)
{
}

void Joueur::Load() {
	Sprite::Load();
	vies = Constants::VAISSEAU_VIES;
	visible = true;
	x = Constants::START_X;
	y = Constants::START_Y;
	vx = 0;
	vy = 0;
}

void Joueur::UpdatePhasePrincipale(float dt)
{
	//deplacement
	if (IsKeyDown(KEY_UP)) {
		vy -= Constants::ACCELERATION;
	}
	else if (IsKeyDown(KEY_DOWN)) {
		vy += Constants::ACCELERATION;
	}

	if (IsKeyDown(KEY_LEFT)) {
		vx -= Constants::ACCELERATION ;
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		vx += Constants::ACCELERATION;
	}
	
	vx *= Constants::DECELERATION;
	vy *= Constants::DECELERATION;

	Vaisseau::UpdatePhasePrincipale(dt);

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
