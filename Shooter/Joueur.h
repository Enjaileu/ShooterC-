#pragma once
#include "Vaisseau.h"
class Joueur :
    public Vaisseau
{
public:
    Joueur(float xP, float yP, int viesP);
    void Load() override;
    void Update(float dt);
};

