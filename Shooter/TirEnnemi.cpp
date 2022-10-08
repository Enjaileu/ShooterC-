#include "TirEnnemi.h"
#include "Constants.h"

TirEnnemi::TirEnnemi(float xP, float yP, float rotationP, float vitesseP):
	Sprite("assets/tir_ennemi.png", xP, yP, rotationP, true),
	vitesse{vitesseP}
{
}

void TirEnnemi::Update(float dt)
{
	x -= cos(rotation) * abs(vitesse) * dt;
	y -= sin(rotation) * abs(vitesse) * dt;
}
