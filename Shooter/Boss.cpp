#include "Boss.h"
#include "Constants.h"

Boss::Boss(float xP, float yP, int viesP):
	Vaisseau("assets/boss.png", xP, yP, 0, viesP)
{
}

void Boss::Update(float dt)
{
	Vaisseau::Update(dt);
	switch (etat)
	{
	case EtatBoss::ChoixDeplacement:
		UpdateChoixDeplacement();
		break;
	case EtatBoss::Deplacement:
		UpdateDeplacement(dt);
		break;
	case EtatBoss::AttenteTir:
		UpdateAttenteTir(dt);
		break;
	case EtatBoss::Tir:
		UpdateTir(dt);
		break;
	case EtatBoss::SuperTir:
		UpdateSuperTir(dt);
		break;
	case EtatBoss::AttenteFin:
		UpdateAttenteFin(dt);
		break;
	default:
		UpdateChoixDeplacement();
		break;
	}

	//gestion tir
	for (int i = tirs.size() - 1; i >=0; --i) {
		tirs[i].Update(dt);
		tirs[i].Draw();
		if (tirs[i].x <= -16 
			|| tirs[i].x >= Constants::SCREEN_WIDTH + 16
			|| tirs[i].y <= -16
			|| tirs[i].y >= Constants::SCREEN_HEIGHT + 16) {
			tirs[i].Unload();
			tirs.erase(begin(tirs) + i);
		}
	}
}

void Boss::UpdateChoixDeplacement()
{
	float numRand = (float)rand() / (float)RAND_MAX;
	cibleX = numRand * (Constants::SCREEN_WIDTH - Constants::SCREEN_WIDTH / 3 - 96) + Constants::SCREEN_WIDTH / 3;
	numRand = (float)rand() / (float)RAND_MAX;
	cibleY = numRand * (Constants::SCREEN_HEIGHT - 96 - 48) + 48;

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
	if (chrono >= Constants::BOSS_CHRONO) {
		chrono = 0;
		etat = EtatBoss::Tir;
	}
	else {
		chrono += dt;
	}
}

void Boss::UpdateTir(float dt)
{
	chrono += dt;
	if(chrono >= Constants::BOSS_INTERVAL_TIR && nbTir < 3){
		nbTir++;
		TirEnnemi tir{ x - 52 ,y, 0, Constants::TIR_VITESSE};
		tir.Load();
		tirs.push_back(tir);
		chrono = 0;
	}
	else if (chrono >= Constants::BOSS_CHRONO_TIR) {
		etat = EtatBoss::SuperTir;
		chrono = 0;
		nbTir = 0;
	}
	
}

void Boss::UpdateSuperTir(float dt)
{
	if (nbTir == 0) {
		nbTir++;
		for (int i = 0; i < Constants::BOSS_NB_SUPERTIR; ++i) {
			TirEnnemi tir(x - 52, y, 2.f * PI / Constants::BOSS_NB_SUPERTIR * i, Constants::BOSS_SUPERTIR_VITESSE);
			tir.Load();
			tirs.push_back(tir);
		}
	}
	else {
		nbTir = 0;
		etat = EtatBoss::ChoixDeplacement;
	}
}

void Boss::UpdateAttenteFin(float dt)
{
	chrono += dt;
	if (chrono >= Constants::BOSS_ATTENTE_FIN) {
		chrono = 0;
		etat = EtatBoss::ChoixDeplacement;
	}
}
