#include "EtatJeu.h"
#include <time.h> 

void EtatJeu::Load() {
	vaisseau.Load();
	srand(time(nullptr));
	compteur = 0.f;
}
void EtatJeu::Update(float dt) {
	compteur += dt;
	//mouv vaisseau
	vaisseau.Update(dt);

	//gestion tir
	for (Tir* tir : tirs) {
		tir->Update(dt);
	}
	for (int i = tirs.size() - 1; i >= 0; --i) {
		if (tirs[i]->x > Constants::SCREEN_WIDTH) {
			tirs[i]->Unload();
			tirs.erase(begin(tirs) + i);
		}
	}
	if (IsKeyPressed(KEY_SPACE)) {
		tirs.push_back(vaisseau.Tirer());
	}

	//gestion ennemi
	if (compteur >= 2) {
		Ennemi ennemi{ (float)Constants::SCREEN_WIDTH + 16, 0, 0 };
		ennemi.Load();
		ennemis.push_back(ennemi);
		compteur = 0;
	}
	UpdateEnnemis(dt);
}
void EtatJeu::Draw() {
	vaisseau.Draw();
	for (Tir* tir : tirs) {
		tir->Draw();
	}
	for (Ennemi ennemi : ennemis) {
		ennemi.Draw();
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

void EtatJeu::UpdateEnnemis(float dt)
{
	for (int j = ennemis.size() - 1; j >= 0; --j) {
		ennemis[j].Update(dt);
		if (ennemis[j].x < -16) {
			ennemis[j].Unload();
			ennemis.erase(begin(ennemis) + j);
		}
	}
}
