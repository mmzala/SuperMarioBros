#pragma once

#include "CharacterSettings.h"
#include "MovementComponentSettings.h"

struct MarioSettings : CharacterSettings
{
	MovementComponentSettings movementSettings;

	/// <summary>
	/// How long it takes to power up
	/// </summary>
	float poweringUpTime;

	MarioSettings(MovementComponentSettings movementSettings = MovementComponentSettings(), float powerinUpTime = 0.0f)
		:
		CharacterSettings::CharacterSettings(),
		movementSettings(movementSettings),
		poweringUpTime(poweringUpTime)
	{}
};