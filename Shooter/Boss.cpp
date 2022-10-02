#include "Boss.h"
#include "Constants.h"

Boss::Boss(float xP, float yP):
	Vaisseau("assets/boss.png", xP, yP, 0)
{
}

void Boss::Update(float dt)
{
	Vaisseau::Update(dt);
	switch (etat)
	{
	case EtatBoss::ChoixDeplacement:
		UpdateChoixDeplacement();
		//TraceLog(LOG_INFO, "Etat Choix Deplacement");
		break;
	case EtatBoss::Deplacement:
		UpdateDeplacement(dt);
		//TraceLog(LOG_INFO, "Etat Deplacement");
		break;
	case EtatBoss::AttenteTir:
		UpdateAttenteTir(dt);
		TraceLog(LOG_INFO, "Etat Attente");
		break;
	case EtatBoss::Tir:
		//updateTir(dt);
		break;
	case EtatBoss::SuperTir:
		//updateSuperTir(dt);
		break;
	case EtatBoss::AttenteFin:
		//updateAttenteFin(dt);
		break;
	default:
		//updateChoixDeplacement();
		break;
	}
}

void Boss::UpdateChoixDeplacement()
{
	float numRand = (float)rand() / (float)RAND_MAX;
	cibleX = numRand * (Constants::SCREEN_WIDTH - Constants::SCREEN_WIDTH / 3 - 96) + Constants::SCREEN_WIDTH / 3;
	numRand = (float)rand() / (float)RAND_MAX;
	cibleY = 48 * numRand + ((Constants::SCREEN_HEIGHT - 96) * numRand);

	etat = EtatBoss::Deplacement;
}

void Boss::UpdateDeplacement(float dt)
{
	if (y < cibleY) {
		vy = Constants::BOSS_VITESSE;
	}
	else if (y > cibleY) {
		vy = -Constants::BOSS_VITESSE;
	}
	 
	if (x < cibleX) {
		vx = Constants::BOSS_VITESSE;
	}
	else if (x > cibleX) {
		vx = -Constants::BOSS_VITESSE;
	}
	
	chrono += dt;
	
	
	if (abs(y - cibleY) < Constants::BOSS_VITESSE * 0.75f) {
		vy = 0;
	}

	if (abs(cibleX-x) < Constants::BOSS_VITESSE * 0.75f) {
		vx = 0;
	}

	if (vy == 0 && vx == 0) {
		etat = EtatBoss::AttenteTir;
	}
}

void Boss::UpdateAttenteTir(float dt)
{
	//TraceLog(LOG_INFO, " % f >= % f", chrono, Constants::BOSS_CHRONO);
	if (chrono >= Constants::BOSS_CHRONO) {
		chrono = 0;
		etat = EtatBoss::ChoixDeplacement;
	}
	else {
		chrono += dt;
	}
}
