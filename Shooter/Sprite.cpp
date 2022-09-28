#include "Sprite.h"
#include "GestionTextures.h"
#include <string>

Sprite::Sprite(std::string pathP, float xP, float yP, float rotationP, bool centeredP) :
	path{ pathP },
	x{ xP },
	y{ yP },
	rotation{ rotationP },
	centered{ centeredP }{}

void Sprite::Load() {
	texture = GestionTexture::Get(path);
	if (centered) {
		origin = { (float)(texture.width / 2),
				   (float)(texture.height / 2) };
	}
	srcRect = { 0.f, 0.f, (float)texture.width, (float)texture.height };
}

void Sprite::Draw() {
	if (visible) {
		float rotationDegres = rotation * 180.f / PI;
		dstRect = { x, y, (float)texture.width, (float)texture.height };
		DrawTexturePro(texture, srcRect, dstRect, origin, rotationDegres, WHITE);
	}
}

void Sprite::Unload() {
	//UnloadTexture(texture);
}

Rectangle Sprite::GetRectangle() {
	Rectangle rect{ x - origin.x, y - origin.y, (float)texture.width,  (float)texture.height };
	return rect;
}
