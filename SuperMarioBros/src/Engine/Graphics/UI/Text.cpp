#include "Text.h"
#include "../../../Game/GameObjects/Components/Transform.h"
#include <cstring> // strlen

Text::Text(TextSettings settings)
	:
	Sprite::Sprite(settings),
	UIElement::UIElement(),
	text(),
	minAsciiCode(settings.minAsciiCode), // 32 for current font
	maxAsciiCode(settings.maxAsciiCode), // 126 for current font
	spacing(settings.spacing)
{}

Text::~Text()
{}

void Text::Draw(const DirectX::XMFLOAT2& anchor)
{
	DirectX::XMFLOAT2 originalPosition = transform->position;
	float spriteSizeX = GetSize().x * transform->scale.x;
	transform->position.y += anchor.y;

	for (int i = 0; i < text.length(); i++)
	{
		int asciiCode = int(text[i]);
		if (!CharacterIsInScope(asciiCode)) continue;
		transform->position.x = (float)(i * (spriteSizeX + spacing) + originalPosition.x + anchor.x);
		SetFrame(asciiCode - minAsciiCode);
		Sprite::Draw(transform->GetWorldMatrix());
	}

	transform->position = originalPosition;
}

void Text::SetText(std::string text)
{
	this->text = text;
}

bool Text::CharacterIsInScope(int asciiCode)
{
	if (asciiCode >= minAsciiCode &&
		asciiCode <= maxAsciiCode)
	{
		return true;
	}

	return false;
}
