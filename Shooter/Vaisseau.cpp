#include "Vaisseau.h"
#include "Constants.h"

Vaisseau::Vaisseau(std::string cheminTextureP, float rotationP,
	CoteEcran coteEcranEntreeP, CoteEcran coteEcranSortieP,
	float xCibleP, float yCibleP,
	float dureePhasePrincipaleP, int vieP) :
	Sprite{ cheminTextureP, 0, 0, rotationP, true },
	coteEcranEntree{coteEcranEntreeP},
	coteEcranSortie{coteEcranSortieP},
	xCible{xCibleP},
	yCible{yCibleP},
	dureePhasePrincipale{dureePhasePrincipaleP},
	vies{vieP}
{
	ChangerPhase(Phase::Entree);
}

void Vaisseau::Update(float dt) {
	switch (phase) {
	case Phase::Entree:
		UpdatePhaseEntree(dt);
		break;
	case Phase::Principale:
		UpdatePhasePrincipale(dt);
		break;
	case Phase::Sortie:
		UpdatePhaseSortie(dt);
		break;
	}
}
Tir* Vaisseau::Tirer() {
	Rectangle rect = GetRectangle();
	Tir* tir = new Tir(rect.x + rect.width, y, 0, Constants::TIR_VITESSE);
	tir->Load();
	return tir;
}

bool Vaisseau::Degats(int degatsP)
{
	vies -= degatsP;
	if (vies <= 0) {
		return true;
	}
	return false;
}

bool Vaisseau::HorsJeu() {
	return phase == Phase::Sortie && vx == 0 && vy == 0 &&
		(x < 0 || x > Constants::SCREEN_WIDTH ||
			y < 0 || y > Constants::SCREEN_HEIGHT);
}

void Vaisseau::ExecuterDeplacement(float dt)
{
	x += vx * dt;
	y += vy *dt;
}


void Vaisseau::ChangerPhase(Phase nouvellePhase) {
	switch (nouvellePhase) {
	case Phase::Entree:
		phase = Phase::Entree;
		switch (coteEcranEntree) {
		case CoteEcran::Gauche:
			x = xCible - Constants::SCREEN_WIDTH;
			y = yCible;
			break;
		case CoteEcran::Droite:
			x = xCible + Constants::SCREEN_WIDTH;
			y = yCible;
			break;
		case CoteEcran::Haut:
			x = xCible;
			y = yCible - Constants::SCREEN_HEIGHT;
			break;
		case CoteEcran::Bas:
			x = xCible;
			y = yCible + Constants::SCREEN_HEIGHT;
			break;
		}
		break;
	case Phase::Principale:
		compteurPhasePrincipale = 0.0f;
		phase = Phase::Principale;
		break;
	case Phase::Sortie:
		phase = Phase::Sortie;
		switch (coteEcranSortie) {
		case CoteEcran::Gauche:
			xCible = x - Constants::SCREEN_WIDTH * 2;
			break;
		case CoteEcran::Droite:
			xCible = x + Constants::SCREEN_WIDTH * 2;
			break;
		case CoteEcran::Haut:
			yCible = y - Constants::SCREEN_HEIGHT * 2;
			break;
		case CoteEcran::Bas:
			yCible = y + Constants::SCREEN_HEIGHT * 2;
			break;
		}
		break;
	}
}

void Vaisseau::UpdatePhaseEntree(float dt) {
	DeplacementVersCible(dt);
	ExecuterDeplacement(dt);
	if (vx == 0 && vy == 0) {
		phase = Phase::Principale;
	}
}

void Vaisseau::UpdatePhasePrincipale(float dt) {
	ExecuterDeplacement(dt);
	if (dureePhasePrincipale != -1) {
		compteurPhasePrincipale += dt;
		if (compteurPhasePrincipale >= dureePhasePrincipale) {
			ChangerPhase(Phase::Sortie);
		}
	}
}

void Vaisseau::UpdatePhaseSortie(float dt) {
	DeplacementVersCible(dt);
	ExecuterDeplacement(dt);
	if (vx == 0 && vy == 0) {
		visible = false;
	}
}

void Vaisseau::DeplacementVersCible(float dt) {
	float vitessePlacement = Constants::VITESSE_PLACEMENT;
	if (x < xCible) {
		vx = vitessePlacement;
	} 
	else if (x > xCible) {
		vx = -vitessePlacement;
	}
	if (abs(x - xCible) < vitessePlacement * dt) {
		vx = 0;
	}
	if (y < yCible) {
		vy = vitessePlacement;
	}
	else if (y > yCible) {
		vy = -vitessePlacement;
	}
	if (abs(y - yCible) < vitessePlacement * dt) {
		vy = 0;
	}
}