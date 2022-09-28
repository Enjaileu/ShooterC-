#pragma once
#include "raylib.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct TextureStockee {
	string fichier;
	Texture2D texture;
};

class GestionTexture {
public:
	GestionTexture(vector<string> chargementTextures);
	void Load();
	void Unload();
	static Texture2D Get(string fichier);
private:
	vector<string> fichiers;
	static vector<TextureStockee> stock;
};

