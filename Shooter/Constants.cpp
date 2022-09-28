#include "Constants.h"
#include <cmath>

//SCREEN
const int Constants::SCREEN_WIDTH{ 900 };
const int Constants::SCREEN_HEIGHT{ 600 };

//UI
const int Constants::VERTICAL_SEPARATION{ 25 };

// Serpent
const int Constants::SEGMENT_TAILLE{ 16 };
const float Constants::HORLOGE{ 0.15f };
const float Constants::SERPENT_DEPART_X{ SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 2) % SEGMENT_TAILLE };
const float Constants::SERPENT_DEPART_Y{ SCREEN_HEIGHT / 2 - (SCREEN_HEIGHT / 2) % SEGMENT_TAILLE };

// Carte
const int Constants::CARTE_TAILLE_X{ 32 };
const int Constants::CARTE_TAILLE_Y{ 32 };

float Constants::CoordX(int xCarte) {
	return SCREEN_WIDTH / 2
		- (SCREEN_WIDTH / 2) % (int)SEGMENT_TAILLE
		- CARTE_TAILLE_X * SEGMENT_TAILLE / 2
		+ xCarte * SEGMENT_TAILLE;
}
float Constants::CoordY(int yCarte) {
	return SCREEN_HEIGHT / 2
		- (SCREEN_HEIGHT / 2) % (int)SEGMENT_TAILLE
		- CARTE_TAILLE_Y * SEGMENT_TAILLE / 2
		+ (yCarte + 1) * SEGMENT_TAILLE; // Décalage
}

int Constants::CarteX(float x) {
	float xNormalise = x - SCREEN_WIDTH / 2 + CARTE_TAILLE_X / 2 * SEGMENT_TAILLE;
	return round(xNormalise) / (int)Constants::SEGMENT_TAILLE + 1;
}
int Constants::CarteY(float y) {
	float yNormalise = y - SCREEN_HEIGHT / 2 + CARTE_TAILLE_Y / 2 * SEGMENT_TAILLE;
	return round(yNormalise) / (int)Constants::SEGMENT_TAILLE;
}