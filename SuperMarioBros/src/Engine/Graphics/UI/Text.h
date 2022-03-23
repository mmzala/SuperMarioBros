#pragma once

#include "../Sprite.h"
#include "../../../Game/Settings/TextSettings.h"

class Transform;

class Text : private Sprite
{
public:
	Text(TextSettings settings);
	~Text() override;

	void Draw();
	void SetText(const char* text);

private:
	bool CharacterIsInScope(int asciiCode);

public:
	Transform* transform;

private:
	const char* text;
	const int minAsciiCode;
	const int maxAsciiCode;
	const float spacing;
};

