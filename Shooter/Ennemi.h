#pragma once
#include "Vaisseau.h"
class Ennemi :
    public Vaisseau
{
public:
    Ennemi(float xP, float yP, float rotationP, int viesP);
    void Update(float dt);

private:
    void PositionnerHauteur();
};

