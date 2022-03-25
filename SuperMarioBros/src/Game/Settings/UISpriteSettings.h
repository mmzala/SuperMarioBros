#pragma once

#include "SpriteSettings.h"
#include "../../Engine/Graphics/Animation.h"

struct UISpriteSettings : SpriteSettings
{
	Animation animation;

	UISpriteSettings(Animation animation = Animation())
		:
		SpriteSettings::SpriteSettings(),
		animation(animation)
	{}
};