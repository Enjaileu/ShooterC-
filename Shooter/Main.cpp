#include "raylib.h"
#include "Constants.h"
#include "GestionTextures.h"
#include "EtatJeu.h"
#include "EtatMenu.h"
#include "EtatGameover.h"
//declaration
//------------------------------------------------------------------

void Load();
void Draw();
void Update();
void Unload();
void GererChangementEtat();
void ChangerEtat(Etat* nouvelEtat);

EtatMenu etatMenu{};
EtatJeu etatJeu{};
EtatGameover etatGameover{};
Etat* etatCourant = &etatMenu;

vector<string> nomsTextures{
	"assets/vaisseau.png",
	"assets/tir.png",
	"assets/ennemi.png",
	"assets/boss.png",
	"assets/tir_ennemi.png",
	"assets/titre.png",
	"assets/jouer_select.png",
	"assets/jouer_passif.png",
	"assets/quitter_select.png",
	"assets/quitter_passif.png",
	"assets/gameoverTitre.png",
	"assets/ciel.png"
};
GestionTexture gestionTexture{ nomsTextures };

//Code et définition
//------------------------------------------------------------------

void Load() {
	InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Shooter");
	SetTargetFPS(60);

	gestionTexture.Load();
	etatCourant->Load();
}

void Draw() {

	BeginDrawing();
	ClearBackground(BLACK);
	etatCourant->Draw();

	EndDrawing();
}
void Update() {
	float dt = GetFrameTime();
	etatCourant->Update(dt);
	GererChangementEtat();
}

void Unload() {
	gestionTexture.Unload();
	etatCourant->Unload();

	CloseWindow();
}

void GererChangementEtat() {
	ProchainEtat prochainEtat = etatCourant->prochainEtat();
	switch (prochainEtat)
	{
	case ProchainEtat::Menu:
		ChangerEtat(&etatMenu);
		break;
	case ProchainEtat::Jeu:
		ChangerEtat(&etatJeu);
		break;
	case ProchainEtat::Gameover:
		ChangerEtat(&etatGameover);
		break;
	default:
		break;
	}
}

void ChangerEtat(Etat* nouvelEtat) {
	etatCourant->Unload();
	etatCourant = nouvelEtat;
	etatCourant->Load();
}

int main() {
	Load();

	while (!WindowShouldClose()) {
		Update();
		Draw();
	}

	Unload();
	return 0;
}