#pragma once

#include "../World/Tilemap.h"
#include "SpriteSettings.h"

struct CharacterSettings
{
	SpriteSettings spriteSettings;
	Tilemap* tilemap;
	float walkingSpeed;
	float gravity;

	CharacterSettings(SpriteSettings spriteSettings = SpriteSettings(), Tilemap* tilemap = nullptr, 
		float walkingSpeed = 0.0f, float gravity = 0.0f)
		:
		spriteSettings(spriteSettings),
		tilemap(tilemap),
		walkingSpeed(walkingSpeed),
		gravity(gravity)
	{}
};