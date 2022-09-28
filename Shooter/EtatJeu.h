#pragma once
#include "Etat.h"
#include "Vaisseau.h"

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

    Vaisseau vaisseau{ 100.f, 100.f, 0 };
};


