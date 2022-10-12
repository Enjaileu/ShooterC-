#include "EtatJeu.h"
#include <time.h> 
#include <string>
#include <cmath>

void EtatJeu::Load() {
	joueur.Load();
	srand(time(nullptr));
	compteurGameover = 0.0f;
	compteur = 0;
	compteurVagues = 0;
	for (int i = 0; i < Constants::NB_VAGUES; ++i) {
		Vague vague{ i + 1 };
		vagues.push_back(vague);
	}
	for (Parallaxe& parallaxe : parallaxes) {
		parallaxe.Load();
	}
}

void EtatJeu::Update(float dt) {
	compteur += dt;
	//mouv vaisseau
	if (joueur.visible) {
		joueur.Update(dt);
	}
	else {
		UpdateGameover(dt);
	}

	//gestion tir
	if (IsKeyPressed(KEY_SPACE)) {
		tirs.push_back(joueur.Tirer());
	}
	else if (IsKeyPressed(KEY_B)) {
		AttaqueBouclier();
	}

	for (Tir* tir : tirs) {
		tir->Update(dt);
	}

	for (int i = tirs.size() - 1; i >= 0; --i) {
		if (tirs[i]->x > Constants::SCREEN_WIDTH) {
			tirs[i]->Unload();
			tirs.erase(begin(tirs) + i);
		}
	}
	
	//gestion ennemi - boss

	UpdateEnnemis(dt);

	if (boss.etat != EtatBoss::Inactif) {
		boss.Update(dt);
	}

	UpdateCollisions(dt);
	UpdateGameover(dt);	
	UpdateParallaxes(dt);
}

void EtatJeu::Draw() {
	for (Parallaxe& parallaxe : parallaxes) {
		parallaxe.Draw();
	}

	if(joueur.visible){
		joueur.Draw();
	}
	
	for (Tir* tir : tirs) {
		tir->Draw();
	}
	for (Ennemi ennemi : ennemis) {
		ennemi.Draw();
	}
	if (boss.etat != EtatBoss::Inactif) {
		boss.Draw();
	}

	std::string text = "Vies du joueur = " + std::to_string(joueur.vies);
	DrawText(text.c_str(), 10, 10, 16, WHITE);
}

void EtatJeu::Unload() {
	joueur.Unload();

	for (Parallaxe& parallaxe : parallaxes) {
		parallaxe.Unload();
	}
}

ProchainEtat EtatJeu::prochainEtat()
{
	ProchainEtat nouvelEtat = transition;
	transition = ProchainEtat::None;
	return nouvelEtat;
}

void EtatJeu::UpdateEnnemis(float dt)
{
	// Apparition
	//compteur += dt;
	if (compteur >= Constants::ENNEMI_INTERVAL && compteurVagues < Constants::NB_VAGUES)
	{
		vagues[compteurVagues].ParametrerVague(ennemis, boss);
		++compteurVagues;
		compteur -= Constants::ENNEMI_INTERVAL;
	}

	//update
	for (int i = ennemis.size() - 1; i >= 0; --i) {
		ennemis[i].Update(dt);
		// Sortie de l'ecran
		if (ennemis[i].HorsJeu()) {
			ennemis[i].Unload();
			ennemis.erase(begin(ennemis) + i);
		}
	}

	
}

void EtatJeu::UpdateCollisions(float dt)
{
	
	Rectangle rectBoss = boss.GetRectangle();
	Rectangle rectJoueur = joueur.GetRectangle();

	
	if (boss.etat != EtatBoss::Inactif && joueur.visible) {
		// boss-joueur
		if (CheckCollisionRecs(rectBoss, rectJoueur)) {
			if (joueur.Degats(1)){
				joueur.visible = false;
			}
			
		}

		// boss-tirs du joueur
		for (int i = tirs.size() - 1; i >= 0; i--) {
			Rectangle rectTir = tirs[i]->GetRectangle();
			if (CheckCollisionRecs(rectTir, rectBoss)) {
				tirs[i]->Unload();
				tirs.erase(begin(tirs) + i);
				if (boss.Degats(1)) {
					boss.visible = false;
				}
			}
		}

		//tirs du boss - joueur
		for (int i = boss.tirs.size() - 1; i >= 0; --i) {
			Rectangle rectTir = boss.tirs[i].GetRectangle();
			if (CheckCollisionRecs(rectJoueur, rectTir)) {
				boss.tirs[i].Unload();
				boss.tirs.erase(begin(boss.tirs) + i);
				if (joueur.Degats(1)) {
					joueur.visible = false;
				}

			}
		}
	}
	
	// ennemis-joueur
	for (int i = ennemis.size() - 1; i >= 0; --i) {
		Rectangle rectEnnemi = ennemis[i].GetRectangle();
		if (CheckCollisionRecs(rectEnnemi, rectJoueur)) {
			if (joueur.Degats(1)) {
				joueur.visible = false;
			}
			ennemis[i].Unload();
			ennemis.erase(begin(ennemis) + i);
		}
		// ennemis-tirs du joueur
		for (int j = tirs.size() - 1; j >= 0; --j) {
			Rectangle rectTir = tirs[j]->GetRectangle();
			if (CheckCollisionRecs(rectTir, rectEnnemi)) {
				if(ennemis[i].Degats(1)){
					ennemis[i].Unload();
					ennemis.erase(begin(ennemis) + i);
				}
				tirs[j]->Unload();
				tirs.erase(begin(tirs) + j);
			}
		}
	}
}

void EtatJeu::AttaqueBouclier() {
	TraceLog(LOG_INFO, "attaque bouclier");
	for (int i = boss.tirs.size() - 1; i >= 0; --i) {
		float dx = abs(joueur.x - boss.tirs[i].x);
		float dy = abs(joueur.y - boss.tirs[i].y);
		TraceLog(LOG_INFO, "dx = %f  dy = %f  ==> distance : %f", dx, dy, dx * dx + dy * dy);

		if (dx * dx + dy * dy <= Constants::BOUCLIER_DISTANCE* Constants::BOUCLIER_DISTANCE) {
			TraceLog(LOG_INFO, "tir suppr");
			boss.tirs[i].Unload();
			boss.tirs.erase(begin(boss.tirs) + i);
		}
	}
}

void EtatJeu::UpdateGameover(float dt)
{
	if (joueur.vies <= 0) {
		compteurGameover += dt;
		if (compteurGameover >= Constants::DUREE_GAME_OVER) {
			for (int i = ennemis.size() - 1; i >= 0; --i) {
				ennemis[i].Unload();
				ennemis.erase(begin(ennemis) + i);
			}
			transition = ProchainEtat::Gameover;
		}
	}
}

void EtatJeu::UpdateParallaxes(float dt) {
	for (Parallaxe& parallaxe : parallaxes) {
		parallaxe.Update(dt);
	}
}