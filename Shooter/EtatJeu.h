#pragma once
#include "Etat.h"
#include "Vaisseau.h"
#include "Constants.h"
#include "Tir.h"
#include "Ennemi.h"
#include <vector>
using std::vector;

class EtatJeu :
    public Etat
{
public:
    void Load() override;
    void Update(float dt) override;
    void Draw() override;
    void Unload() override;

private:

    ProchainEtat prochainEtat() override;
    ProchainEtat transition{ ProchainEtat::None };

    Vaisseau vaisseau{ Constants::START_X, Constants::START_Y, 0 };

    vector<Tir*> tirs{};

    float compteur;

    vector<Ennemi> ennemis{};
    void UpdateEnnemis(float dt);
};


