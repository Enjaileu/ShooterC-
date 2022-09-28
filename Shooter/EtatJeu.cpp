#include "EtatJeu.h"

void EtatJeu::Load() {
}
void EtatJeu::Update(float dt) {
}
void EtatJeu::Draw() {
}
void EtatJeu::Unload() {

}
ProchainEtat EtatJeu::prochainEtat()
{
	ProchainEtat nouvelEtat = transition;
	transition = ProchainEtat::None;
	return nouvelEtat;
}
