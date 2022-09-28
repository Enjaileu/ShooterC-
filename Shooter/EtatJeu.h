#pragma once
#include "Etat.h"
#include "Vaisseau.h"
#include "Constants.h"

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
};


