#pragma once
#include "Etat.h"
#include "Sprite.h"
#include "Constants.h"

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

private:
    Sprite titre{ "assets/titre.png", Constants::SCREEN_WIDTH / 2, 100, 0, true };
};

