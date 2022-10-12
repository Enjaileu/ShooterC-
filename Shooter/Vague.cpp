#include "Vague.h"

Vague::Vague(int id) {
	string chemin = "ressources/vague" + to_string(id) + ".txt";
	ifstream fichier{ chemin };

	// Enregistrer chaque ligne du fichier
	string ligne;
	while (getline(fichier, ligne)) {
		lignesFichier.push_back(ligne);
	}
	fichier.close();

	// S�parer la premi�re ligne en mots
	// pour donner une valeur au chronom�tre
	string premiereLigne{ lignesFichier[0] };
	istringstream premiereLigneStream{ premiereLigne };
	vector<string> mots;
	string mot;
	while (getline(premiereLigneStream, mot, ' ')) {
		mots.push_back(mot);
	}
	chrono = stof(mots[1]);
}

void Vague::ParametrerVague(vector<Ennemi>& ennemis, Boss& boss)
{
	for (string ligne : lignesFichier) {

		// Lecture mot par mot
		istringstream ligneStream{ ligne };
		vector<string> mots;
		string mot;
		while (getline(ligneStream, mot, ' ')) {
			mots.push_back(mot);
		}
		// Ignorer la premi�re ligne
		if (mots[0] == "chrono") { continue; }

		// Param�trage vague
		CoteEcran coteEntree{ GetCoteEcran(mots[1]) };
		CoteEcran coteSortie{ GetCoteEcran(mots[2]) };
		float xCible = stof(mots[3]);
		float yCible = stof(mots[4]);
		float dureePhasePrincipale = stof(mots[5]);
		if (mots[0] == "ennemi") {
			Ennemi ennemi{ xCible, yCible, PI, coteEntree,
			coteSortie, dureePhasePrincipale, 1 };
			ennemi.Load();
			ennemis.push_back(ennemi);
		}
		else if (mots[0] == "boss") {
			boss.Parametrer(xCible, yCible, coteEntree, coteSortie);
		}
	}
}

CoteEcran Vague::GetCoteEcran(string s)
{
	if (s == "gauche") {
		return CoteEcran::Gauche;
	}
	else if (s == "droite") {
		return CoteEcran::Droite;
	}
	else if (s == "haut") {
		return CoteEcran::Haut;
	}
	else {
		return CoteEcran::Bas;
	}
}
