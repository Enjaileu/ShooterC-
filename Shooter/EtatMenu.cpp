#include "EtatMenu.h"
#include "raylib.h"
#include "Constants.h"

void EtatMenu::Load() {
    titre.Load();
    for (Bouton& bouton : boutons) {
        bouton.Load();
    }
}

void EtatMenu::Update(float dt) {
    // Mise à jour du bouton selectionné
    if (!boutons[indexBouton].GetSelection()) {
        for (Bouton& bouton : boutons) {
            bouton.SetSelection(false);
        }
        boutons[indexBouton].SetSelection(true);
    }
    // Utilisation du clavier pour changer de bouton
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        indexBouton = (indexBouton + 1) % maxIndexBouton;
    }
    else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        indexBouton = (indexBouton - 1 + maxIndexBouton)
            % maxIndexBouton;
    }
    // Validation du bouton
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        switch (indexBouton) {
        case 0:
            transition = ProchainEtat::Jeu;
            break;
        case 1:
            CloseWindow();
            break;
        }
    }
}
void EtatMenu::Draw() {
    titre.Draw();
    for (Bouton& bouton : boutons) {
        bouton.Draw();
    }
}
void EtatMenu::Unload() {
    titre.Unload(); 
    for (Bouton& bouton : boutons) {
        bouton.Unload();
    }
}

ProchainEtat EtatMenu::prochainEtat()
{
    ProchainEtat nouvelEtat = transition;
    transition = ProchainEtat::None;
    return nouvelEtat;
}
