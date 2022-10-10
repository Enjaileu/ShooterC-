#pragma once
#include "Sprite.h"
#include "Constants.h"

using namespace std;

class Bouton :
    public Sprite
{
public:
    Bouton(string cheminTextureSelP, string cheminTextureDeselP,
        float xP, float yP);
    void Load() override;
    void Unload() override;
    bool GetSelection();
    void SetSelection(bool selectionP);
private:
    Texture2D textureSelectionne;
    Texture2D textureDeselectionne;
    string cheminTextureSel;
    bool selection{ false };
};

