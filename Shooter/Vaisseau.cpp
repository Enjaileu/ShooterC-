#include "Vaisseau.h"
#include "Constants.h"

Vaisseau::Vaisseau(std::string cheminTextureP, float xP, float yP, float rotationP) :
	Sprite{ cheminTextureP, xP, yP, rotationP, true }
{
}
void Vaisseau::Update(float dt) {
	x += vx;
	y += vy;
}
Tir* Vaisseau::Tirer() {
	Rectangle rect = GetRectangle();
	Tir* tir = new Tir(rect.x + rect.width, y);
	tir->Load();
	return tir;
}