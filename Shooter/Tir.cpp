#include "Tir.h"
#include "Constants.h"


Tir::Tir(float xP, float yP, float rotationP, float vitesseP) :
	Sprite("assets/tir_ennemi.png", xP, yP, rotationP, true),
	vitesse{ vitesseP }
{
}

void Tir::Update(float dt)
{
	x += cos(rotation) * vitesse * dt;
	y += sin(rotation) * vitesse * dt;
}