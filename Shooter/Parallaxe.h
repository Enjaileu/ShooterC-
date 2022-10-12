#pragma once

#include "Sprite.h"
#include <string>
#include <vector>

using namespace std;

class Parallaxe {
public:
	Parallaxe(string chemin, int nbImagesP, float vitesseDefilementP, int largeurImageP);
	void Load();
	void Update(float dt);
	void Draw();
	void Unload();
private:
	vector<Sprite> images;
	int nbImages;
	float vitesseDefilement;
	int largeurImage;
};