#include "AIMovementComponent.h"
#include "../Character.h"

AIMovementComponent::AIMovementComponent(Character* character)
	:
	character(character),
	walkingRight(false)
{}

AIMovementComponent::~AIMovementComponent()
{}

void AIMovementComponent::Update()
{
	// If velocity is 0 that means we hit something, so we change direction
	if (character->velocity.x == 0.0f) walkingRight = !walkingRight;

	character->velocity.y = -character->gravity;
	character->velocity.x = character->walkingSpeed * (walkingRight ? 1 : -1);
}
