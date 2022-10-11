#pragma once
#include "Vaisseau.h"
class Ennemi :
    public Vaisseau
{
public:
    Ennemi(float xP, float yP, float rotationP, CoteEcran entreeP, CoteEcran sortieP, float dureePhasePrincipaleP, int viesP);
    void UpdatePhasePrincipale(float dt) override;

private:
    void PositionnerHauteur();
};

