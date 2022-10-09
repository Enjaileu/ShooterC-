#include "EtatMenu.h"
#include "raylib.h"
#include "Constants.h"

void EtatMenu::Load() {
    titre.Load();
}
void EtatMenu::Update(float dt) {
    if (IsKeyPressed(KEY_SPACE)) {
        transition = ProchainEtat::Jeu;
    }
}
void EtatMenu::Draw() {
    titre.Draw();
}
void EtatMenu::Unload() {
    titre.Unload();
}

ProchainEtat EtatMenu::prochainEtat()
{
    ProchainEtat nouvelEtat = transition;
    transition = ProchainEtat::None;
    return nouvelEtat;
}
