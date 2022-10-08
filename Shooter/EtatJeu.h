#pragma once
#include "Etat.h"
#include "Joueur.h"
#include "Constants.h"
#include "Tir.h"
#include "Ennemi.h"
#include "Boss.h"

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

    Joueur joueur{ Constants::START_X, Constants::START_Y, 3};

    vector<Tir*> tirs{};

    float compteur{ 0.f };

    vector<Ennemi> ennemis{};
    void UpdateEnnemis(float dt);

    Boss boss{ Constants::BOSS_START_X, Constants::BOSS_START_Y, 10};
    float compteurBoss{ 0.f };
    bool isBoss{ false };

    void UpdateCollisions(float dt);
};


