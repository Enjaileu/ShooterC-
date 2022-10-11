#pragma once
#include "Sprite.h"
#include "Tir.h"
#include <string>
#include "Phase.h"
#include "CoteEcran.h"

class Vaisseau : public Sprite {
public:
	Vaisseau(std::string cheminTextureP, float rotationP,
		CoteEcran coteEcranEntreeP, CoteEcran coteEcranSortieP,
		float xCibleP, float yCibleP, 
		float dureePhasePrincipaleP, int vieP);
	virtual void Update(float dt);
	Tir* Tirer();
	bool Degats(int degatsP);
	float vx{ 0.0f };
	float vy{ 0.0f };
	int vies;
	bool HorsJeu();

private:
	void ExecuterDeplacement(float dt);
	void DeplacementVersCible(float dt);

protected:
	Phase phase{ Phase::Entree };
	CoteEcran coteEcranEntree{ CoteEcran::Droite };
	CoteEcran coteEcranSortie{ CoteEcran::Gauche };
	float xCible{ 0.0f };
	float yCible{ 0.0f };
	float dureePhasePrincipale{ 0.0f };
	float compteurPhasePrincipale{ 0.0f };
	
	void ChangerPhase(Phase nouvellePhase);
	void UpdatePhaseEntree(float dt);
	virtual void UpdatePhasePrincipale(float dt) = 0;
	void UpdatePhaseSortie(float dt);
};

