#pragma once

#include "raylib.h"
#include "Particule.h"
#include <vector>
#include <string>

using namespace std;

class SystemeParticules {
public:
	SystemeParticules(float x, float y, Color couleur);
	void Update();
	void Draw();
	int MAX_PARTICULES{ 100 };
	vector<Particule> particules;
	bool actif{ true };
};