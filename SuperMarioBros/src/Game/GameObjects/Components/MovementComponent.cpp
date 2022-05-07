#include "MovementComponent.h"
#include "../Character.h"
#include "../../../Utils/Math.h" // Lerp
#include <cmath> // fmax / fmin
#include "../../../Engine/Physics/TilemapCollider.h" // Checking if is grounded

MovementComponent::MovementComponent(Character* character, MovementComponentSettings settings)
	:
	character(character),
	state(MovementState::Standing),
	isGrounded((character->tilemapCollider->DetectedCollisions()& CheckSide::Bottom) == CheckSide::Bottom),
	movementDirection(0),
	runningSpeed(settings.runningSpeed),
	walkingAcceleration(settings.walkingAcceleration),
	runningAcceleration(settings.runningAcceleration),
	releaseDeceleration(settings.releaseDeceleration),
	skiddingDeceleration(settings.skiddingDeceleration),
	skidTurnaroundSpeed(settings.skidTurnaroundSpeed),
	runningDecelerationDelay(settings.runningDecelerationDelay),
	runningDecelerationTimer(runningDecelerationDelay),
	airWalkingTurnaroundSpeed(settings.airWalkingTurnaroundSpeed),
	airRunningTurnaroundSpeed(settings.airRunningTurnaroundSpeed),
	minJumpSpeed(settings.minJumpSpeed),
	maxJumpSpeed(settings.maxJumpSpeed),
	maxJumpTime(settings.maxJumpTime),
	jumpDecelaration(settings.jumpDecelaration),
	jumpTimer(maxJumpTime),
	isJumping(false),
	forceJump(false)
{}

MovementComponent::~MovementComponent()
{}

void MovementComponent::Update(MovementInput input, const float deltaTime)
{
	CheckSide collisions = character->tilemapCollider->DetectedCollisions();
	isGrounded = (collisions & CheckSide::Bottom) == CheckSide::Bottom;
	MoveHorizontal(input.left, input.right, input.run, input.duck, deltaTime);
	MoveVertical(input.jump, input.duck, deltaTime);
}

void MovementComponent::ForceJump()
{
	forceJump = true;
}

MovementState MovementComponent::GetState()
{
	return state;
}

int MovementComponent::GetMovementDirection()
{
	return movementDirection;
}

bool MovementComponent::IsGrounded()
{
	return isGrounded;
}

// REFACTOR THIS LATER PLS
void MovementComponent::MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const bool duckInput, const float deltaTime)
{
	float movementSpeed = ShouldRun(runInput, deltaTime) ? runningSpeed : character->walkingSpeed;
	float movementAccelertion = (runInput ? runningAcceleration : walkingAcceleration) * deltaTime;
	float turnaroundSpeed = GetTurnaroundSpeed() * deltaTime;
	movementDirection = rightInput - leftInput;

	if (!duckInput) // Can't move when ducking
	{
		if (leftInput && !rightInput)  // Left movement
		{
			// If velocity is too high then go back to the max velocity slowly
			if (-movementSpeed > character->velocity.x && isGrounded)
			{
				character->velocity.x = character->velocity.x + releaseDeceleration * deltaTime;
			}
			else
			{
				if (character->velocity.x > 0.0f)
				{
					state = MovementState::TurningAround;
					character->velocity.x = character->velocity.x - turnaroundSpeed;
				}
				else
				{
					state = MovementState::Running;
					character->velocity.x = std::fmax(character->velocity.x - movementAccelertion, -movementSpeed);
				}
			}
		}

		if (rightInput && !leftInput) // Right movement
		{
			if (movementSpeed < character->velocity.x && isGrounded)
			{
				character->velocity.x = character->velocity.x - releaseDeceleration * deltaTime;
			}
			else
			{
				if (character->velocity.x < 0.0f)
				{
					state = MovementState::TurningAround;
					character->velocity.x = character->velocity.x + turnaroundSpeed;
				}
				else
				{
					state = MovementState::Running;
					character->velocity.x = std::fmin(character->velocity.x + movementAccelertion, movementSpeed);
				}
			}
		}
	}

	if (((!leftInput && !rightInput || leftInput && rightInput)) || duckInput) // No input or both input or duck input
	{
		state = duckInput ? MovementState::Ducking : MovementState::Standing;
		if (!isGrounded) return;

		if (character->velocity.x < 0)
		{
			character->velocity.x = std::fmin(0.0f, character->velocity.x + skiddingDeceleration * deltaTime);
		}
		else if (character->velocity.x > 0)
		{
			character->velocity.x = std::fmax(0.0f, character->velocity.x - skiddingDeceleration * deltaTime);
		}
	}
}

// REFACTOR THIS LATER PLS
void MovementComponent::MoveVertical(const bool jumpInput, const bool duckInput, const float deltaTime)
{
	if (character->velocity.y > 0.0f)
	{
		character->velocity.y = character->velocity.y - jumpDecelaration * deltaTime;
	}
	else
	{
		character->velocity.y = std::fmax(character->velocity.y - character->gravityAcceleration * deltaTime, -character->gravity);
	}

	if (jumpInput || forceJump)
	{
		if (jumpTimer > 0.0f || forceJump)
		{
			// If top collision is detected then stop jumping
			if ((character->tilemapCollider->DetectedCollisions() & CheckSide::Top) == CheckSide::Top)
			{
				jumpTimer = 0.0f;
			}
			else
			{
				character->velocity.y = Math::Lerp(maxJumpSpeed, minJumpSpeed, jumpTimer / maxJumpTime);
			}

			isJumping = true;
			forceJump = false;
			jumpTimer -= deltaTime;
		}

		if (isGrounded) isJumping = false;
	}
	else
	{
		if (isGrounded)
		{
			jumpTimer = maxJumpTime;
			isJumping = false;
		}
		else
		{
			jumpTimer = 0.0f;
		}
	}

	if (isJumping && !duckInput) state = MovementState::Jumping;
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
