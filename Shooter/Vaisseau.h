#pragma once
#include "Sprite.h"
class Vaisseau :
    public Sprite
{
public:
    Vaisseau(float xP, float yP, float rotationP);
    void Update(float dt);
    void Load();

private:
    float vx;
    float vy;
    float width;
    float height;
};

