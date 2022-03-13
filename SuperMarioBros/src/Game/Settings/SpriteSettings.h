#pragma once

#include <DirectXMath.h>

struct SpriteSettings
{
	const char* textureFile;
	DirectX::XMINT2 spriteSheetSize;

	/// <summary>
	/// Creates settings, which decide how the sprite will function.
	/// </summary>
	/// <param name="textureFile">: What texture file to use </param>
	/// <param name="spriteSheetSize">: Sprite sheet size that contains 2^n animation frames (example: size 2 == 4 frames / size 3 == 9 frames) </param>
	SpriteSettings(const char* textureFile = nullptr, DirectX::XMINT2 spriteSheetSize = DirectX::XMINT2(1, 1))
		:
		textureFile(textureFile),
		spriteSheetSize(spriteSheetSize)
	{}
};