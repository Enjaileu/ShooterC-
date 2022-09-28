#include "EtatGameover.h"
#include "raylib.h"
#include "Constants.h"

void EtatGameover::Load() {
}
void EtatGameover::Update(float dt) {
    if (IsKeyPressed(KEY_SPACE)) {
        transition = ProchainEtat::Menu;
    }
}
void EtatGameover::Draw() {
    DrawText("Game Over", Constants::SCREEN_WIDTH / 2 - 50, Constants::SCREEN_HEIGHT / 2, 20, WHITE);
    DrawText("Press [SPACE] to back to the menu.", Constants::SCREEN_WIDTH / 2 - 200, Constants::SCREEN_HEIGHT / 2 + 25, 20, WHITE);
}
void EtatGameover::Unload() {
}

ProchainEtat EtatGameover::prochainEtat()
{
    ProchainEtat nouvelEtat = transition;
    transition = ProchainEtat::None;
    return nouvelEtat;
}

