#include "EtatJeu.h"
#include <time.h> 
#include <string>
#include <cmath>

void EtatJeu::Load() {
	joueur.Load();
	boss.Load();
	srand(time(nullptr));
}
void EtatJeu::Update(float dt) {
	compteur += dt;
	compteurBoss += dt;
	//mouv vaisseau
	if (joueur.visible) {
		joueur.Update(dt);
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
	if (compteurBoss >= 5.f) {
		compteurBoss = 0;
		isBoss = true;
	}

	if (!isBoss) {
		if (compteur >= 2) {
			Ennemi ennemi{ (float)Constants::SCREEN_WIDTH + 16, 0, 0, 1 };
			ennemi.Load();
			ennemis.push_back(ennemi);
			compteur = 0;
		}
	}
	else {
		if (boss.visible) {
			boss.Update(dt);
		}
	}
	UpdateEnnemis(dt);

	UpdateCollisions(dt);

	
}
void EtatJeu::Draw() {
	if(joueur.visible){
		joueur.Draw();
	}
	
	for (Tir* tir : tirs) {
		tir->Draw();
	}
	for (Ennemi ennemi : ennemis) {
		ennemi.Draw();
	}
	if (boss.visible) {
		boss.Draw();
	}

	std::string text = "Vies du joueur = " + std::to_string(joueur.vies);
	DrawText(text.c_str(), 10, 10, 16, WHITE);

}
void EtatJeu::Unload() {
	joueur.Unload();
}
ProchainEtat EtatJeu::prochainEtat()
{
	return ProchainEtat::None;
}

void EtatJeu::UpdateEnnemis(float dt)
{
	for (int j = ennemis.size() - 1; j >= 0; --j) {
		ennemis[j].Update(dt);
		//ennemi trop loin
		if (ennemis[j].x < -16) {
			ennemis[j].Unload();
			ennemis.erase(begin(ennemis) + j);
		}

	}
}

void EtatJeu::UpdateCollisions(float dt)
{
	
	Rectangle rectBoss = boss.GetRectangle();
	Rectangle rectJoueur = joueur.GetRectangle();

	
	if (boss.visible && joueur.visible) {
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
