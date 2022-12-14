#include "Constants.h"
#include <cmath>

//SCREEN
const float Constants::SCREEN_WIDTH{ 800.f };
const float Constants::SCREEN_HEIGHT{ 600.f };

//UI
const int Constants::VERTICAL_SEPARATION{ 25 };

//VAISSEAU
const float Constants::START_X{ 100.f };
const float Constants::START_Y{ 100.f };
const float Constants::ACCELERATION{ 500.f };
const float Constants::DECELERATION{ 0.58f };
const int Constants::VAISSEAU_VIES{ 5 };
const float Constants::VITESSE_PLACEMENT{ 800.f };

//TIR
const float Constants::TIR_VITESSE{ 1000.f };
const float Constants::BOUCLIER_DISTANCE{ 50.f };

//ENNEMI
const float Constants::ENNEMI_VITESSE_X{ -10.f };
const float Constants::ENNEMI_VITESSE_Y{ 6.f };
const float Constants::ENNEMI_MAX_VX{ -3.f };
const float Constants::ENNEMI_MAX_VY{ 6.f };
const float Constants::ENNEMI_INTERVAL{ 2.f };

//BOSS
const float Constants::BOSS_CHRONO{ 2.f };
const float Constants::BOSS_START_X{ SCREEN_WIDTH + 100 };
const float Constants::BOSS_START_Y{ SCREEN_HEIGHT / 2 };
const float Constants::BOSS_VITESSE{ 500.f };
const float Constants::BOSS_CHRONO_TIR{ 2.0f };
const float Constants::BOSS_INTERVAL_TIR{ 0.33f };
const int Constants::BOSS_NB_SUPERTIR{ 16 };
const int Constants::BOSS_NB_TIR{ 5 };
const float Constants::BOSS_SUPERTIR_VITESSE{ 400.f };
const float Constants::BOSS_ATTENTE_FIN{ 2.f };

//JEU
const float Constants::DUREE_GAME_OVER{ 2.f };
const int Constants::NB_VAGUES{ 3 };