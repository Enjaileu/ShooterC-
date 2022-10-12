#include "Boss.h"
#include "Constants.h"

Boss::Boss(float xP, float yP, CoteEcran entreeP, CoteEcran sortieP, int viesP):
	Vaisseau("assets/boss.png", 0, entreeP, sortieP, xP, yP, -1, viesP)
{
}

void Boss::Load()
{
	Sprite::Load();
	rotation = 0;
	vies = 20;
	etat = EtatBoss::ChoixDeplacement;
	chrono = 0.0f;
	cibleY = 0.0f;
	cibleX = 0.f;
	x = Constants::BOSS_START_X;
	y = Constants::BOSS_START_Y;
	visible = true;
}

void Boss::UpdatePhasePrincipale(float dt)
{
	
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

	Vaisseau::UpdatePhasePrincipale(dt);
}

void Boss::Parametrer(float xCibleP, float yCibleP, CoteEcran entree, CoteEcran sortie)
{
	Load();
	etat = EtatBoss::ChoixDeplacement;
	xCible = xCibleP;
	yCibleP = yCibleP;
	coteEcranEntree = entree;
	coteEcranSortie = sortie;
	visible = true;
	ChangerPhase(Phase::Entree);
}

void Boss::UpdateChoixDeplacement()
{
	TraceLog(LOG_INFO, "UpdateChoixDeplacement");
	float numRand = (float)rand() / (float)RAND_MAX;
	cibleX = numRand * (Constants::SCREEN_WIDTH - Constants::SCREEN_WIDTH / 3 - 96) + Constants::SCREEN_WIDTH / 3;
	numRand = (float)rand() / (float)RAND_MAX;
	cibleY = numRand * (Constants::SCREEN_HEIGHT - 96 - 48) + 48;

	etat = EtatBoss::Deplacement;
}

void Boss::UpdateDeplacement(float dt)
{
	TraceLog(LOG_INFO, "UpdateDeplacement");
	if (y < cibleY) {
		vy = Constants::BOSS_VITESSE;
	}
	else if (y > cibleY) {
		vy = -Constants::BOSS_VITESSE ;
	}
	 
	if (x < cibleX) {
		vx = Constants::BOSS_VITESSE ;
	}
	else if (x > cibleX) {
		vx = -Constants::BOSS_VITESSE ;
	}
	
	chrono += dt;
	
	if (abs(y - cibleY) < Constants::BOSS_VITESSE * 0.75f * dt) {
		vy = 0;
	}

	if (abs(cibleX-x) < Constants::BOSS_VITESSE * 0.75f * dt) {
		vx = 0;
	}
	
	if (vy == 0 && vx == 0) {
		etat = EtatBoss::AttenteTir;
	}
}

void Boss::UpdateAttenteTir(float dt)
{
	TraceLog(LOG_INFO, "UpdateAttenteTir");
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
	TraceLog(LOG_INFO, "UpdateTir");
	chrono += dt;
	if (chrono >= Constants::BOSS_NB_TIR * Constants::BOSS_INTERVAL_TIR) {
		chrono = 0;
		etat = EtatBoss::SuperTir;
	}
}

void Boss::UpdateSuperTir(float dt)
{
	TraceLog(LOG_INFO, "UpdateSuperTir");
}

void Boss::UpdateAttenteFin(float dt)
{
	TraceLog(LOG_INFO, "UpdateAttenteFin");
	chrono += dt;
	if (chrono >= Constants::BOSS_ATTENTE_FIN) {
		chrono = 0;
		etat = EtatBoss::ChoixDeplacement;
	}
}

Tir* Boss::Tirer(float rotationP){
	Rectangle rect = GetRectangle();
	Tir* tir = new Tir(rect.x - rect.width/2, y, rotationP, -Constants::TIR_VITESSE);
	tir->Load();
	return tir;
}
