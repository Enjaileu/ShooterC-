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
	for (Tir* tir : tirsBoss) {
		tir->Update(dt);
	}

	for (int i = tirs.size() - 1; i >= 0; --i) {
		if (tirs[i]->x > Constants::SCREEN_WIDTH) {
			tirs[i]->Unload();
			tirs.erase(begin(tirs) + i);
		}
	}

	// gestion ennemi - boss
	UpdateEnnemis(dt);

	if (boss.etat != EtatBoss::Inactif) {
		boss.Update(dt);
		if (boss.etat == EtatBoss::Tir) {
			compteurBossTir += dt;
			if (compteurBossTir >= Constants::BOSS_INTERVAL_TIR) {
				TraceLog(LOG_INFO, "Boss tir");
				tirsBoss.push_back(boss.Tirer(0));
				compteurBossTir = 0;
			}

		}
		else if (boss.etat == EtatBoss::SuperTir) {
			for (int i = 0; i < Constants::BOSS_NB_SUPERTIR; ++i) {
				tirsBoss.push_back(boss.Tirer(2.f * PI / Constants::BOSS_NB_SUPERTIR * i));
			}
			boss.etat = EtatBoss::AttenteFin;
		}
	}

	UpdateCollisions(dt);
	UpdateGameover(dt);
	UpdateParallaxes(dt);
	UpdateParticules();
}

void EtatJeu::Draw() {
	for (Parallaxe& parallaxe : parallaxes) {
		parallaxe.Draw();
	}

	if (boss.etat != EtatBoss::Inactif) {
		boss.Draw();
	}

	if(joueur.visible){
		joueur.Draw();
	}
	
	for (Tir* tir : tirs) {
		tir->Draw();
	}
	for (Tir* tir : tirsBoss) {
		tir->Draw();
	}

	for (Ennemi ennemi : ennemis) {
		ennemi.Draw();
	}

	for (SystemeParticules& systeme : particules) {
		systeme.Draw();
	}

	std::string text = "Vies du joueur = " + std::to_string(joueur.vies);
	DrawText(text.c_str(), 10, 10, 16, WHITE);
}

void EtatJeu::Unload() {
	joueur.Unload();

	for (Parallaxe& parallaxe : parallaxes) {
		parallaxe.Unload();
	}

	particules.clear();
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
				particules.emplace_back(tirs[i]->x, tirs[i]->y, ORANGE);
				tirs[i]->Unload();
				tirs.erase(begin(tirs) + i);
				TraceLog(LOG_INFO, "%i", boss.vies);
				if (boss.Degats(1)) {
					boss.visible = false;
					boss.etat = EtatBoss::Inactif;
				}
			}
		}

		//tirs du boss - joueur
		for (int i = tirsBoss.size() - 1; i >= 0; --i) {
			Rectangle rectTir = tirsBoss[i]->GetRectangle();
			if (CheckCollisionRecs(rectJoueur, rectTir)) {
				particules.emplace_back(tirsBoss[i]->x, tirsBoss[i]->y, ORANGE);
				tirsBoss[i]->Unload();
				tirsBoss.erase(begin(tirsBoss) + i);
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
				particules.emplace_back(tirs[j]->x, tirs[j]->y, ORANGE);
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
	for (int i = tirsBoss.size() - 1; i >= 0; --i) {
		float dx = abs(joueur.x - tirsBoss[i]->x);
		float dy = abs(joueur.y - tirsBoss[i]->y);
		TraceLog(LOG_INFO, "dx = %f  dy = %f  ==> distance : %f", dx, dy, dx * dx + dy * dy);

		if (dx * dx + dy * dy <= Constants::BOUCLIER_DISTANCE* Constants::BOUCLIER_DISTANCE) {
			TraceLog(LOG_INFO, "tir suppr");
			tirsBoss[i]->Unload();
			tirsBoss.erase(begin(tirsBoss) + i);
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

void EtatJeu::UpdateParticules() {
	// Mise à jour
	for (SystemeParticules& systeme : particules) {
		systeme.Update();
	}
	// Suppression
	for (int i = particules.size() - 1; i >= 0; --i) {
		if (!particules[i].actif) {
			particules.erase(begin(particules) + i);
		}
	}
}