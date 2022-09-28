#include "GestionTextures.h"

vector<TextureStockee> GestionTexture::stock{};

GestionTexture::GestionTexture(
	vector<string> chargementTextures) :
	fichiers{ chargementTextures }
{}

void GestionTexture::Load() {
	// Texture par défaut stockée en premier
	Texture2D textureDefault = LoadTexture("assets/defaut.png");
	TextureStockee stockeeDefaut{ "defaut", textureDefault };
	stock.push_back(stockeeDefaut);
	// Autres textures
	for (string fichier : fichiers) {
		Texture2D texture = LoadTexture(fichier.c_str());
		TextureStockee stockee{ fichier, texture };
		stock.push_back(stockee);
	}
}

Texture2D GestionTexture::Get(string nom) {
	for (TextureStockee& textureStockee : stock) {
		if (textureStockee.fichier == nom) {
			return textureStockee.texture;
		}
	}
	// Pas de texture avec ce nom,
	// renvoie la texture par défaut
	TraceLog(LOG_WARNING, "La texture [%s] n'existe pas dans le gestionnaire de textures.", nom.c_str());
	return stock[0].texture;
}

void GestionTexture::Unload() {
	for (TextureStockee textureStockee : stock) {
		UnloadTexture(textureStockee.texture);
	}
}