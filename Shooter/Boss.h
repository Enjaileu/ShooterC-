#pragma once
#include "Vaisseau.h"
#include "EtatBoss.h"
#include "TirEnnemi.h"
#include <vector>

using std::vector;

class Boss :
    public Vaisseau
{
public:
    Boss(float xP, float yP, int viesP);
    void Update(float dt);
    vector<TirEnnemi> tirs{ };

private:

    void UpdateChoixDeplacement();
    void UpdateDeplacement(float dt);
    void UpdateAttenteTir(float dt);
    void UpdateTir(float dt);
    void UpdateSuperTir(float dt);
    void UpdateAttenteFin(float dt);

    EtatBoss etat = EtatBoss::ChoixDeplacement;
    float cibleX{ 0.f };
    float cibleY{ 0.f };
    float chrono{ 0.f };

    int nbTir{ 0 };
};

