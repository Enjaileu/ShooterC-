#include "Bouton.h"
#include "GestionTextures.h"

Bouton::Bouton(string cheminTextureSelP,
	string cheminTextureDeselP, float xP, float yP) :
	Sprite{ cheminTextureDeselP, xP, yP, 0, true },
	cheminTextureSel{ cheminTextureSelP }
{
}
void Bouton::Load() {
	Sprite::Load();
	textureSelectionne = GestionTexture::Get(cheminTextureSel);
	textureDeselectionne = texture;
}

void Bouton::Unload() {
	Sprite::Unload();
}

bool Bouton::GetSelection() {
	return selection;
}
void Bouton::SetSelection(bool selectionP) {
	selection = selectionP;
	if (selection) {
		texture = textureSelectionne;
	}
	else {
		texture = textureDeselectionne;
	}
}