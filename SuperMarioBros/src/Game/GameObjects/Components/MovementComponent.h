#pragma once

#include "../../Settings/MovementComponentSettings.h"

class Character;

struct MovementInput
{
	bool left;
	bool right;
	bool run;
	bool jump;

	MovementInput(bool left = false, bool right = false, bool run = false, bool jump = false)
		:
		left(left),
		right(right),
		run(run),
		jump(jump)
	{}
};

enum class MovementState
{
	Standing = 0,
	Walking = 1,
	Running = 2,
	Jumping = 3,
};

class MovementComponent
{
public:
	MovementComponent(Character* character, MovementComponentSettings settings);
	~MovementComponent();

	void Update(MovementInput input, const float deltaTime);
	MovementState GetState();

private:
	void MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const float deltaTime);

private:
	Character* character;
	MovementState state;

	// Movement variables
	float runningSpeed;
	float walkingAcceleration;
	float runningAcceleration;
	float releaseDeceleration;
	float skiddingDeceleration;
	float skidTurnaroundSpeed;
	float runningDecelerationDelay;
	float runningDecelerationTimer;
};

