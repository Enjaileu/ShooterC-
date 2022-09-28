#pragma once
#include "Sprite.h"
class Vaisseau :
    public Sprite
{
public:
    Vaisseau(float xP, float yP, float rotationP);
    void Update(float dt);

private:
    float vx;
    float vy;
};

