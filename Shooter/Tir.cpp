#include "Tir.h"
#include "Constants.h"

Tir::Tir(float xP, float yP):
	Sprite("assets/tir.png", xP, yP, 0, true)
{
}

void Tir::Update(float dt) {
	x += Constants::TIR_VITESSE * dt;
}
