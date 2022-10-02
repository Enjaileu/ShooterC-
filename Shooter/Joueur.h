#pragma once
#include "Vaisseau.h"
class Joueur :
    public Vaisseau
{
public:
    Joueur(float xP, float yP);
    void Update(float dt);
};

