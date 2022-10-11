#pragma once
#include "Vaisseau.h"
class Joueur :
    public Vaisseau
{
public:
    Joueur(float xP, float yP, CoteEcran entreeP, CoteEcran sortieP, int viesP);
    void Load() override;
    void UpdatePhasePrincipale(float dt) override;
};

