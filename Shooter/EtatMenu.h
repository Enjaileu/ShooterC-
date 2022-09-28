#pragma once
#include "Etat.h"

class EtatMenu :
    public Etat
{
public:
    void Load() override;
    void Update(float dt) override;
    void Draw() override;
    void Unload() override;
    ProchainEtat prochainEtat() override;

    ProchainEtat transition = ProchainEtat::None;
};

