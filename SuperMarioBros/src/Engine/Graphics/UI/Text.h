#pragma once

#include "../Sprite.h"
#include "UIElement.h"
#include "../../../Game/Settings/TextSettings.h"

class Text : private Sprite, public UIElement
{
public:
	Text(TextSettings settings);
	~Text() override;

	void Draw(DirectX::XMFLOAT2 anchor) override;
	void SetText(const char* text);

private:
	bool CharacterIsInScope(int asciiCode);

private:
	const char* text;
	const int minAsciiCode;
	const int maxAsciiCode;
	const float spacing;
};

