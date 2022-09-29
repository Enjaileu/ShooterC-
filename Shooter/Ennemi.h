#pragma once
#include "Sprite.h"
class Ennemi :
    public Sprite
{
public:
    Ennemi(float xP, float yP, float rotationP);
    void Update(float dt);

private:
    float vx;
    float vy;
    void PositionnerHauteur();
};

