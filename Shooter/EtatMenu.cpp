#include "EtatMenu.h"
#include "raylib.h"
#include "Constants.h"

void EtatMenu::Load() {
}
void EtatMenu::Update(float dt) {
    if (IsKeyPressed(KEY_SPACE)) {
        transition = ProchainEtat::Jeu;
    }
}
void EtatMenu::Draw() {
    DrawText("SHOOTER", 40, 50, 240, WHITE);
    DrawText("Press [SPACE] to play", 50, Constants::SCREEN_HEIGHT - 30, 20, WHITE);
}
void EtatMenu::Unload() {
}

ProchainEtat EtatMenu::prochainEtat()
{
    ProchainEtat nouvelEtat = transition;
    transition = ProchainEtat::None;
    return nouvelEtat;
}
