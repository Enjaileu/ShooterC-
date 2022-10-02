#pragma once
#include "Vaisseau.h"
class Ennemi :
    public Vaisseau
{
public:
    Ennemi(float xP, float yP, float rotationP);
    void Update(float dt);

private:
    void PositionnerHauteur();
};

