#pragma once
#include "Etat.h"
#include "Joueur.h"
#include "Constants.h"
#include "Tir.h"
#include "Ennemi.h"
#include "Boss.h"
#include "Vague.h"
#include "Parallaxe.h"
#include "SystemeParticules.h"

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

    Joueur joueur{ Constants::START_X, Constants::START_Y, CoteEcran::Gauche, CoteEcran::Droite, 5};

    vector<Tir*> tirs{};
    vector<Tir*> tirsBoss{};

    float compteur{ 0.f };

    vector<Ennemi> ennemis{};
    void UpdateEnnemis(float dt);


    void UpdateCollisions(float dt);

    void AttaqueBouclier();

    float compteurGameover{ 0.0f };
    void UpdateGameover(float dt);

    vector<Vague> vagues;
    int compteurVagues{ 0 };

    Boss boss{ Constants::SCREEN_WIDTH - 200, Constants::SCREEN_HEIGHT / 2.0, CoteEcran::Haut, CoteEcran::Bas, 100 };
    float compteurBossTir{ 0.f };

    vector<Parallaxe> parallaxes{
        { "assets/ciel.png", 2, -25.0f, 800 }
    };
    void UpdateParallaxes(float dt);

    void UpdateParticules();
    vector<SystemeParticules> particules;
};


