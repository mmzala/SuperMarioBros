#pragma once

struct MovementComponentSettings
{
	float runningSpeed;
	float walkingAcceleration;
	float runningAcceleration;
	float releaseDeceleration;
	float skiddingDeceleration;
	float skidTurnaroundSpeed;
	float runningDecelerationDelay;
	float airWalkingTurnaroundSpeed;
	float airRunningTurnaroundSpeed;

	MovementComponentSettings(float runningSpeed = 0.0f, float walkingAcceleration = 0.0f,
		float runningAcceleration = 0.0f, float releaseDeceleration = 0.0f, float skiddingDeceleration = 0.0f,
		float skidTurnaroundSpeed = 0.0f, float runningDecelerationDelay = 0.25f, float airWalkingTurnaroundSpeed = 0.0f, 
		float airRunningTurnaroundSpeed = 0.0f)
		:
		runningSpeed(runningSpeed),
		walkingAcceleration(walkingAcceleration),
		runningAcceleration(runningAcceleration),
		releaseDeceleration(releaseDeceleration),
		skiddingDeceleration(skiddingDeceleration),
		skidTurnaroundSpeed(skidTurnaroundSpeed),
		runningDecelerationDelay(runningDecelerationDelay),
		airWalkingTurnaroundSpeed(airWalkingTurnaroundSpeed),
		airRunningTurnaroundSpeed(airRunningTurnaroundSpeed)
	{}
};