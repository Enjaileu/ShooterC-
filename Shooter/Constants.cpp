#include "Constants.h"
#include <cmath>

//SCREEN
const int Constants::SCREEN_WIDTH{ 800 };
const int Constants::SCREEN_HEIGHT{ 600 };

//UI
const int Constants::VERTICAL_SEPARATION{ 25 };

//VAISSEAU
const int Constants::START_X{ 100 };
const int Constants::START_Y{ 100 };
const float Constants::ACCELERATION{ 250.f };
const float Constants::DECELERATION{ 0.58f };
const float Constants::MAX_VY{ 25.0f };
const float Constants::MAX_VX{ 15.0f };

//TIR
const float Constants::TIR_VITESSE{ 1000.f };

//ENNEMI
const float Constants::ENNEMI_VITESSE_X{ -10.f };
const float Constants::ENNEMI_VITESSE_Y{ 6.f };
const float Constants::ENNEMI_MAX_VX{ -3.f };
const float Constants::ENNEMI_MAX_VY{ 6.f };

//BOSS
const float Constants::BOSS_CHRONO{ 1.5f };
const float Constants::BOSS_START_X{ SCREEN_WIDTH + 100 };
const float Constants::BOSS_START_Y{ SCREEN_HEIGHT / 2 };
const float Constants::BOSS_VITESSE{ 100.f };