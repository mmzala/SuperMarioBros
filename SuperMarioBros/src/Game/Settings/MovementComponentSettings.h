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
	float minJumpSpeed;
	float maxJumpSpeed;
	float maxJumpTime;
	float jumpDecelaration;

	MovementComponentSettings(float runningSpeed = 0.0f, float walkingAcceleration = 0.0f,
		float runningAcceleration = 0.0f, float releaseDeceleration = 0.0f, float skiddingDeceleration = 0.0f,
		float skidTurnaroundSpeed = 0.0f, float runningDecelerationDelay = 0.25f, float airWalkingTurnaroundSpeed = 0.0f, 
		float airRunningTurnaroundSpeed = 0.0f, float jumpSpeed = 0.0f, float minJumpSpeed = 0.0f, 
		float maxJumpSpeed  = 0.0f, float maxJumpTime = 0.0f, float jumpDecelaration = 0.0f)
		:
		runningSpeed(runningSpeed),
		walkingAcceleration(walkingAcceleration),
		runningAcceleration(runningAcceleration),
		releaseDeceleration(releaseDeceleration),
		skiddingDeceleration(skiddingDeceleration),
		skidTurnaroundSpeed(skidTurnaroundSpeed),
		runningDecelerationDelay(runningDecelerationDelay),
		airWalkingTurnaroundSpeed(airWalkingTurnaroundSpeed),
		airRunningTurnaroundSpeed(airRunningTurnaroundSpeed),
		minJumpSpeed(minJumpSpeed),
		maxJumpSpeed(maxJumpSpeed),
		maxJumpTime(maxJumpTime),
		jumpDecelaration(jumpDecelaration)
	{}
};