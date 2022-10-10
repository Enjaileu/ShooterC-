#pragma once
#include "Etat.h"
#include "Sprite.h"
#include "Constants.h"
#include <vector>
#include "Bouton.h"

class EtatMenu :
    public Etat
{
public:
    void Load() override;
    void Update(float dt) override;
    void Draw() override;
    void Unload() override;
    ProchainEtat prochainEtat() override;

private:
    Sprite titre{ "assets/titre.png", Constants::SCREEN_WIDTH / 2, 100, 0, true };
    vector<Bouton> boutons{ Bouton { "assets/jouer_select.png",
                                     "assets/jouer_passif.png", 400, 400 },
                            Bouton { "assets/quitter_select.png",
                                     "assets/quitter_passif.png", 400, 500 },
    };

    int indexBouton{ 0 };
    const int maxIndexBouton{ 2 };
    ProchainEtat transition{ ProchainEtat::None };
};

