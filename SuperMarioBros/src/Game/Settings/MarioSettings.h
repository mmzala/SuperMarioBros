#pragma once

#include "CharacterSettings.h"

struct MarioSettings : CharacterSettings
{
	float runningSpeed;
	float walkingAcceleration;
	float runningAcceleration;
	float releaseDeceleration;
	float skiddingDeceleration;
	float skidTurnaroundSpeed;
	unsigned int runningDecelerationDelay;

	MarioSettings(float runningSpeed = 0.0f, float walkingAcceleration = 0.0f, 
		float runningAcceleration = 0.0f, float releaseDeceleration = 0.0f, float skiddingDeceleration = 0.0f,
		float skidTurnaroundSpeed = 0.0f, unsigned int runningDecelerationDelay = 0.25f)
		:
		CharacterSettings::CharacterSettings(),
		runningSpeed(runningSpeed),
		walkingAcceleration(walkingAcceleration),
		runningAcceleration(runningAcceleration),
		releaseDeceleration(releaseDeceleration),
		skiddingDeceleration(skiddingDeceleration),
		skidTurnaroundSpeed(skidTurnaroundSpeed),
		runningDecelerationDelay(runningDecelerationDelay)
	{}
};