#include "EtatJeu.h"

void EtatJeu::Load() {
	vaisseau.Load();
}
void EtatJeu::Update(float dt) {
	vaisseau.Update(dt);
}
void EtatJeu::Draw() {
	vaisseau.Draw();
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
