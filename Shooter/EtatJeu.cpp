#include "EtatJeu.h"

void EtatJeu::Load() {
	vaisseau.Load();
}
void EtatJeu::Update(float dt) {
	vaisseau.Update(dt);
	for (Tir* tir : tirs) {
		tir->Update(dt);
	}

	if (IsKeyPressed(KEY_SPACE)) {
		tirs.push_back(vaisseau.Tirer());
	}
}
void EtatJeu::Draw() {
	vaisseau.Draw();
	for (Tir* tir : tirs) {
		tir->Draw();
	}
}
void EtatJeu::Unload() {
	vaisseau.Unload();
}
ProchainEtat EtatJeu::prochainEtat()
{
	//ProchainEtat nouvelEtat = transition;
	//transition = ProchainEtat::None;
	//return nouvelEtat;
	return ProchainEtat::None;
}
