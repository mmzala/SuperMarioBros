#pragma once

#include "CharacterSettings.h"
#include "MovementComponentSettings.h"

struct MarioSettings : CharacterSettings
{
	MovementComponentSettings movementSettings;
	float poweringUpTime;
	float poweringDownTime;
	float poweringDownFlickeringSpeed;

	MarioSettings(MovementComponentSettings movementSettings = MovementComponentSettings(), float powerinUpTime = 0.0f,
		float poweringDownTime = 0.0f, float poweringDownFlickeringSpeed = 0.0f)
		:
		CharacterSettings::CharacterSettings(),
		movementSettings(movementSettings),
		poweringUpTime(poweringUpTime),
		poweringDownTime(poweringDownTime),
		poweringDownFlickeringSpeed(poweringDownFlickeringSpeed)
	{}
};