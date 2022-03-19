#include "MovementComponent.h"
#include "../Character.h"
#include <cmath> // fmax / fmin
#include "../../../Utils/Debug.h" // Debugging
#include "../../../Engine/Physics/TilemapCollider.h" // Checking if is grounded

MovementComponent::MovementComponent(Character* character, MovementComponentSettings settings)
	:
	character(character),
	state(MovementState::Standing),
	isGrounded(character->tilemapCollider->IsGrounded()),
	runningSpeed(settings.runningSpeed),
	walkingAcceleration(settings.walkingAcceleration),
	runningAcceleration(settings.runningAcceleration),
	releaseDeceleration(settings.releaseDeceleration),
	skiddingDeceleration(settings.skiddingDeceleration),
	skidTurnaroundSpeed(settings.skidTurnaroundSpeed),
	runningDecelerationDelay(settings.runningDecelerationDelay),
	runningDecelerationTimer(0.0f),
	airWalkingTurnaroundSpeed(settings.airWalkingTurnaroundSpeed),
	airRunningTurnaroundSpeed(settings.airRunningTurnaroundSpeed)
{}

MovementComponent::~MovementComponent()
{}

void MovementComponent::Update(MovementInput input, const float deltaTime)
{
	isGrounded = character->tilemapCollider->IsGrounded();
	MoveHorizontal(input.left, input.right, input.run, deltaTime);
	MoveVertical(input.jump, deltaTime);
}

MovementState MovementComponent::GetState()
{
	return state;
}

// REFACTOR THIS LATER PLS
void MovementComponent::MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const float deltaTime)
{
	float movementSpeed = ShouldRun(runInput, deltaTime) ? runningSpeed : character->walkingSpeed;
	float movementAccelertion = runInput ? runningAcceleration : walkingAcceleration;
	float turnaroundSpeed = GetTurnaroundSpeed();

	if (leftInput && !rightInput)  // Left movement
	{
		// If velocity is too high then go back to the max velocity slowly
		if (-movementSpeed > character->velocity.x && isGrounded)
		{
			character->velocity.x = character->velocity.x + releaseDeceleration;
		}
		else
		{
			if (character->velocity.x > 0.0f)
			{
				character->velocity.x = character->velocity.x - turnaroundSpeed;
			}
			else
			{
				character->velocity.x = std::fmax(character->velocity.x - movementAccelertion, -movementSpeed);
			}
		}
	}

	if (rightInput && !leftInput) // Right movement
	{
		if (movementSpeed < character->velocity.x && isGrounded)
		{
			character->velocity.x = character->velocity.x - releaseDeceleration;
		}
		else
		{
			if (character->velocity.x < 0.0f)
			{
				character->velocity.x = character->velocity.x + turnaroundSpeed;
			}
			else
			{
				character->velocity.x = std::fmin(character->velocity.x + movementAccelertion, movementSpeed);
			}
		}
	}

	if ((!leftInput && !rightInput || leftInput && rightInput) && isGrounded) // No input while grounded
	{
		if (character->velocity.x < 0)
		{
			character->velocity.x = std::fmin(0.0f, character->velocity.x + skiddingDeceleration);
		}
		else if (character->velocity.x > 0)
		{
			character->velocity.x = std::fmax(0.0f, character->velocity.x - skiddingDeceleration);
		}
	}

	Debug::Log("Turnaround speed: %f\n", turnaroundSpeed);
}

void MovementComponent::MoveVertical(const bool jumpInput, const float deltaTime)
{
	if (jumpInput)
	{
		character->velocity.y = character->gravity;
	}
	else
	{
		character->velocity.y = -character->gravity;
	}
}

bool MovementComponent::ShouldRun(const bool runInput, const float deltaTime)
{
	// If you stop holding "run" input, but continue running in the same direction, Mario will
	// , keep moving at current speed (runningSpeed) for runningDecelerationDelay amount.
	// That's why you don't lose any speed when firing fireballs while running.
	bool shouldRun = false;
	if (runInput) runningDecelerationTimer = runningDecelerationDelay;
	else
	{
		if (std::abs(character->velocity.x) > character->walkingSpeed)
		{
			runningDecelerationTimer -= deltaTime;

			if (runningDecelerationTimer > 0.0f) shouldRun = true;
		}
	}

	return shouldRun || runInput;
}

float MovementComponent::GetTurnaroundSpeed()
{
	return isGrounded ? skidTurnaroundSpeed : character->velocity.x > character->walkingSpeed ? airRunningTurnaroundSpeed : airWalkingTurnaroundSpeed;
}
