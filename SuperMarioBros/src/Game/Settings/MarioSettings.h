#pragma once

#include "CharacterSettings.h"
#include "MovementComponentSettings.h"

struct MarioSettings : public CharacterSettings
{
	MovementComponentSettings movementSettings;
	float poweringUpTime;
	float poweringDownTime;
	float poweringDownFlickeringSpeed;
	float flagPoleBottomPositionY;
	float poleDescendingSpeed;
	float deathAnimationSpeed;
	float timeBeforeDeathAnimation;
	float timeAfterDeathBeforeSceneChange;

	MarioSettings(MovementComponentSettings movementSettings = MovementComponentSettings(), float poweringUpTime = 0.0f,
		float poweringDownTime = 0.0f, float poweringDownFlickeringSpeed = 0.0f, float flagPoleBottomPositionY = 0.0f,
		float poleDescendingSpeed = 0.0f, float deathAnimationSpeed = 0.0f, float timeBeforeDeathAnimation = 0.0f,
		float timeAfterDeathBeforeSceneChange = 0.0f)
		:
		CharacterSettings::CharacterSettings(),
		movementSettings(movementSettings),
		poweringUpTime(poweringUpTime),
		poweringDownTime(poweringDownTime),
		poweringDownFlickeringSpeed(poweringDownFlickeringSpeed),
		flagPoleBottomPositionY(flagPoleBottomPositionY),
		poleDescendingSpeed(poleDescendingSpeed),
		deathAnimationSpeed(deathAnimationSpeed),
		timeBeforeDeathAnimation(timeBeforeDeathAnimation),
		timeAfterDeathBeforeSceneChange(timeAfterDeathBeforeSceneChange)
	{}
};