#include "EtatGameover.h"
#include "raylib.h"
#include "Constants.h"

void EtatGameover::Load() {
    titreGameover.Load();
}

void EtatGameover::Update(float dt) {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) ){
        transition = ProchainEtat::Menu;
    }
}
void EtatGameover::Draw() {
    titreGameover.Draw();
    DrawText("Press [SPACE] to back to the menu.", Constants::SCREEN_WIDTH / 2 - 200, Constants::SCREEN_HEIGHT / 2 + 25, 20, WHITE);
}
void EtatGameover::Unload() {
    titreGameover.Unload();
}

ProchainEtat EtatGameover::prochainEtat()
{
    ProchainEtat nouvelEtat = transition;
    transition = ProchainEtat::None;
    return nouvelEtat;
}

