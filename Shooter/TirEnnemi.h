#pragma once
#include "Sprite.h"
class TirEnnemi :
    public Sprite
{
public:
    TirEnnemi(float xP, float yP, float rotationP, float vitesseP);
    void Update(float dt);

private:
    float vitesse;
};

