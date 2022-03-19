#pragma once

#include "CharacterSettings.h"
#include "MovementComponentSettings.h"

struct MarioSettings : CharacterSettings
{
	MovementComponentSettings movementSettings;

	MarioSettings(MovementComponentSettings movementSettings = MovementComponentSettings())
		:
		CharacterSettings::CharacterSettings(),
		movementSettings(movementSettings)
	{}
};