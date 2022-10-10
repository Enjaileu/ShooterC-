#pragma once
#include "Etat.h"
#include "Sprite.h"

class EtatGameover :
    public Etat
{
public:
    void Load() override;
    void Update(float dt) override;
    void Draw() override;
    void Unload() override;
    ProchainEtat prochainEtat() override;

private:
    ProchainEtat transition{ ProchainEtat::None };
    Sprite titreGameover{ "assets/gameoverTitre.png",
                            400, 200, 0, true
                        };
};

