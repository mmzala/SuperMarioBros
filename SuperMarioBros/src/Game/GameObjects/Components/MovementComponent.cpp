#include "MovementComponent.h"
#include "../Character.h"
#include <cmath> // fmax / fmin
#include "../../../Utils/Debug.h" // Debugging

MovementComponent::MovementComponent(Character* character, MovementComponentSettings settings)
	:
	character(character),
	state(MovementState::Standing),
	runningSpeed(settings.runningSpeed),
	walkingAcceleration(settings.walkingAcceleration),
	runningAcceleration(settings.runningAcceleration),
	releaseDeceleration(settings.releaseDeceleration),
	skiddingDeceleration(settings.skiddingDeceleration),
	skidTurnaroundSpeed(settings.skidTurnaroundSpeed),
	runningDecelerationDelay(settings.runningDecelerationDelay),
	runningDecelerationTimer(0.0f)
{}

MovementComponent::~MovementComponent()
{}

void MovementComponent::Update(MovementInput input, const float deltaTime)
{
	character->velocity.y = -character->gravity;
	MoveHorizontal(input.left, input.right, input.run, deltaTime);
}

MovementState MovementComponent::GetState()
{
	return state;
}

void MovementComponent::MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const float deltaTime)
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

	float movementSpeed = runInput || shouldRun ? runningSpeed : character->walkingSpeed;
	float movementAccelertion = runInput ? runningAcceleration : walkingAcceleration;

	if (leftInput && !rightInput)  // Left movement
	{
		// If velocity is too high then go back to the max velocity slowly
		if (-movementSpeed > character->velocity.x)
		{
			character->velocity.x = character->velocity.x + releaseDeceleration;
		}
		else
		{
			if (character->velocity.x > 0.0f)
			{
				character->velocity.x = character->velocity.x - skidTurnaroundSpeed;
			}
			else
			{
				character->velocity.x = std::fmax(character->velocity.x - movementAccelertion, -movementSpeed);
			}
		}
	}

	if (rightInput && !leftInput) // Right movement
	{
		if (movementSpeed < character->velocity.x)
		{
			character->velocity.x = character->velocity.x - releaseDeceleration;
		}
		else
		{
			if (character->velocity.x < 0.0f)
			{
				character->velocity.x = character->velocity.x + skidTurnaroundSpeed;
			}
			else
			{
				character->velocity.x = std::fmin(character->velocity.x + movementAccelertion, movementSpeed);
			}
		}
	}

	if (!leftInput && !rightInput || leftInput && rightInput) // No input
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

	Debug::Log("character->velocity X: %f\n", character->velocity.x);
}
