#pragma once
#include "Sprite.h"
#include "Tir.h"
#include <string>

class Vaisseau : public Sprite {
public:
	Vaisseau(std::string cheminTextureP, float xP, float yP, float rotationP);
	virtual void Update(float dt);
	Tir* Tirer();
	float vx{ 0.0f };
	float vy{ 0.0f };
};

