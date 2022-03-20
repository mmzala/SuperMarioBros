#pragma once

#include "SpriteSettings.h"

struct FlagSettings
{
	SpriteSettings spriteSettings; 
	DirectX::XMINT2 poleTopPosition; 
	DirectX::XMINT2 poleBottomPosition;
	float descendingSpeed;

	FlagSettings(SpriteSettings spriteSettings = SpriteSettings(), DirectX::XMINT2 poleTopPosition = DirectX::XMINT2(),
		DirectX::XMINT2 poleBottomPosition = DirectX::XMINT2(), float descendingSpeed = 0.0f)
		:
		spriteSettings(spriteSettings),
		poleTopPosition(poleTopPosition),
		poleBottomPosition(poleBottomPosition),
		descendingSpeed(descendingSpeed)
	{}
};