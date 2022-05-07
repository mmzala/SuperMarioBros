#include "Mushroom.h"
#include "Components/AIMovementComponent.h"

// Ignoring collision
#include "../../Engine/Physics/CharacterCollider.h"
#include "Goomba.h"

Mushroom::Mushroom(CharacterSettings settings)
	:
	PowerUp::PowerUp(settings),
	movementComponent(new AIMovementComponent(this))
{
	characterCollider->AddCharacterTypeToIgnore<Goomba>();
	movementComponent->ChangeMovingDirection(); // Begin with moving to the right
}

Mushroom::~Mushroom()
{
	delete movementComponent;
}

void Mushroom::Move(const float deltaTime)
{
	movementComponent->Update(deltaTime);
	Character::Move(deltaTime);
}

void Mushroom::OnCharacterHit(Character* other)
{
	movementComponent->ChangeMovingDirection();
}
