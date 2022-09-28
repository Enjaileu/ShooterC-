#pragma once
#include "raylib.h"
#include <string>

class Sprite
{
public:
	Sprite(std::string pathP, float xP, float yP, float rotationP, bool centreP);
	virtual void Load();
	virtual void Draw();
	virtual void Unload();

	Rectangle GetRectangle();

	std::string path{ "" };
	Texture2D texture;
	float x{ 0.f };
	float y{ 0.f };
	float rotation{ 0.f };
	Vector2 origin{ 0.f, 0.f };
	Rectangle srcRect{ 0.f, 0.f, 0.f, 0.f };
	Rectangle dstRect{ 0.f, 0.f, 0.f, 0.f };
	bool visible{ true };
	bool centered{ false };
};

