#pragma once

#include "../Sprite.h"
#include "UIElement.h"
#include "../../../Game/Settings/UISpriteSettings.h"

class Animator;

/// <summary>
/// Sprite used for UI rendering
/// </summary>
class UISprite : private Sprite, public UIElement
{
public:
	UISprite(UISpriteSettings settings);
	~UISprite() override;

	void Draw(const DirectX::XMFLOAT2& anchor) override;

private:
	Animator* animator;
};

