#include "AIMovementComponent.h"
#include "../Character.h" // For character controlling

AIMovementComponent::AIMovementComponent(Character* character)
	:
	character(character),
	walkingRight(false)
{
	// To prevent changing moving direction on the first update call
	character->velocity.x = character->walkingSpeed * (walkingRight ? 1 : -1);
}

AIMovementComponent::~AIMovementComponent()
{}

void AIMovementComponent::Update(const float deltaTime)
{
	// If velocity is 0 that means we hit something, so we change direction
	if (character->velocity.x == 0.0f) walkingRight = !walkingRight;

	character->velocity.y = std::fmax(character->velocity.y - character->gravityAcceleration * deltaTime, -character->gravity);
	character->velocity.x = character->walkingSpeed * (walkingRight ? 1 : -1);
}

void AIMovementComponent::ChangeMovingDirection()
{
	walkingRight = !walkingRight;
}
