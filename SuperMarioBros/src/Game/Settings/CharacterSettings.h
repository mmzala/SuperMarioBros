#pragma once

#include "../World/Tilemap.h"
#include "SpriteSettings.h"

struct CharacterSettings
{
	SpriteSettings spriteSettings;
	Tilemap* tilemap;
	float movementSpeed;
	float gravity;

	CharacterSettings(SpriteSettings spriteSettings = SpriteSettings(), Tilemap* tilemap = nullptr, 
		float movementSpeed = 0.0f, float gravity = 0.0f)
		:
		spriteSettings(spriteSettings),
		tilemap(tilemap),
		movementSpeed(movementSpeed),
		gravity(gravity)
	{}
};