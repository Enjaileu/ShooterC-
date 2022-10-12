#pragma once
#include "Sprite.h"
class Tir :
    public Sprite
{
public:
    Tir(float xP, float yP, float rotationP, float vitesseP);
    void Update(float dt);
private:
    float vitesse;

};

