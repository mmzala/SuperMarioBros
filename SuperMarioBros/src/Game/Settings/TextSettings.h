#pragma once

#include "SpriteSettings.h"

struct TextSettings : SpriteSettings
{
	int minAsciiCode;
	int maxAsciiCode;
	float spacing;

	TextSettings(int minAsciiCode = 0, int maxAsciiCode = 0, float spacing = 0.0f)
		:
		SpriteSettings(SpriteSettings()),
		minAsciiCode(minAsciiCode),
		maxAsciiCode(maxAsciiCode),
		spacing(spacing)
	{}
};