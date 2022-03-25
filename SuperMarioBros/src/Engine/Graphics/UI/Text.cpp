#include "Text.h"
#include "../../../Game/GameObjects/Components/Transform.h"
#include <cstring> // strlen

Text::Text(TextSettings settings)
	:
	Sprite::Sprite(settings),
	UIElement::UIElement(),
	text(nullptr),
	minAsciiCode(settings.minAsciiCode), // 32 for current font
	maxAsciiCode(settings.maxAsciiCode), // 126 for current font
	spacing(settings.spacing)
{}

Text::~Text()
{}

void Text::Draw(DirectX::XMFLOAT2 anchor)
{
	DirectX::XMFLOAT2 originalPosition = transform->position;
	int textLength = static_cast<int>(std::strlen(text));
	float spriteSizeX = GetSize().x * transform->scale.x;
	transform->position.y += anchor.y;

	for (int i = 0; i < textLength; i++)
	{
		int asciiCode = int(text[i]);
		if (!CharacterIsInScope(asciiCode)) continue;
		transform->position.x = (float)(i * (spriteSizeX + spacing) + originalPosition.x + anchor.x);
		SetFrame(asciiCode - minAsciiCode);
		Sprite::Draw(transform->GetWorldMatrix());
	}

	transform->position = originalPosition;
}

void Text::SetText(const char* text)
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
