#pragma once
#include "Vaisseau.h"
#include "EtatBoss.h"

class Boss :
    public Vaisseau
{
public:
    Boss(float xP, float yP);
    void Update(float dt);

private:

    void UpdateChoixDeplacement();
    void UpdateDeplacement(float dt);
    void UpdateAttenteTir(float dt);

    EtatBoss etat = EtatBoss::ChoixDeplacement;
    float cibleX{ 0.f };
    float cibleY{ 0.f };
    float chrono{ 0.f };
};

