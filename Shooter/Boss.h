#pragma once
#include "Vaisseau.h"
#include "EtatBoss.h"
#include <vector>

using std::vector;

class Boss :
    public Vaisseau
{
public:
    Boss(float xP, float yP, CoteEcran entreeP, CoteEcran sortieP, int viesP);
    void Load() override;
    void UpdatePhasePrincipale(float dt) override;
    void Parametrer(float xCibleP, float yCibleP, CoteEcran entree, CoteEcran sortie);
    EtatBoss etat = EtatBoss::Inactif;
    Tir* Tirer(float rotationP);

private:

    void UpdateChoixDeplacement();
    void UpdateDeplacement(float dt);
    void UpdateAttenteTir(float dt);
    void UpdateTir(float dt);
    void UpdateSuperTir(float dt);
    void UpdateAttenteFin(float dt);

    float cibleX{ 0.f };
    float cibleY{ 0.f };
    float chrono{ 0.f };

    int nbTir{ 0 };
};

