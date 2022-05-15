#include "OneUp.h"
#include "Components/AIMovementComponent.h"

// Ignoring collision
#include "../../Engine/Physics/CharacterCollider.h"
#include "Goomba.h"

OneUp::OneUp(CharacterSettings settings)
	:
	Character::Character(settings),
	movementComponent(new AIMovementComponent(this))
{
	characterCollider->AddCharacterTypeToIgnore<Goomba>();
	movementComponent->ChangeMovingDirection(); // Begin with moving to the right
}

OneUp::~OneUp()
{
	delete movementComponent;
}

void OneUp::Move(const float deltaTime)
{
	movementComponent->Update(deltaTime);
	Character::Move(deltaTime);
}

void OneUp::CheckCollision(const float deltaTime)
{
	Character::CheckCollision(deltaTime);
	CheckFalledOffMap(true);
}

void OneUp::OnCharacterHit(Character* other)
{
	movementComponent->ChangeMovingDirection();
}
