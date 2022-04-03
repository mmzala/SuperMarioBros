#pragma once

#include "../Sprite.h"
#include "UIElement.h"
#include "../../../Game/Settings/TextSettings.h"
#include <string>

class Text : private Sprite, public UIElement
{
public:
	Text(TextSettings settings);
	~Text() override;

	void Draw(DirectX::XMFLOAT2 anchor) override;
	void SetText(std::string text);

private:
	bool CharacterIsInScope(int asciiCode);

private:
	std::string text;
	const int minAsciiCode;
	const int maxAsciiCode;
	const float spacing;
};

