#pragma once
class Constants
{
public:
	//SCREEN
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

	//UI
	static const int VERTICAL_SEPARATION;

	//VAISSEAU
	static const int START_X;
	static const int START_Y;
	static const float ACCELERATION;
	static const float DECELERATION;
	static const float MAX_VY;
	static const float MAX_VX;

	//TIR
	static const float TIR_VITESSE;
	static const float BOUCLIER_DISTANCE;

	//ENNEMI
	static const float ENNEMI_VITESSE_X;
	static const float ENNEMI_VITESSE_Y;
	static const float ENNEMI_MAX_VX;
	static const float ENNEMI_MAX_VY;

	//BOSS
	static const float BOSS_CHRONO;
	static const float BOSS_START_X;
	static const float BOSS_START_Y;
	static const float BOSS_VITESSE;
	static const float BOSS_CHRONO_TIR;
	static const float BOSS_INTERVAL_TIR;
	static const int BOSS_NB_SUPERTIR;
	static const float BOSS_SUPERTIR_VITESSE;
	static const float BOSS_ATTENTE_FIN;

};

