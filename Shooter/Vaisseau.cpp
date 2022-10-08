#include "Vaisseau.h"
#include "Constants.h"

Vaisseau::Vaisseau(std::string cheminTextureP, float xP, float yP, float rotationP, int viesP) :
	Sprite{ cheminTextureP, xP, yP, rotationP, true },
	vies{viesP}
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

bool Vaisseau::Degats(int degatsP)
{
	vies -= degatsP;
	if (vies <= 0) {
		return true;
	}
	return false;
}
