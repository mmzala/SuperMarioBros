#include "Mushroom.h"
#include "Components/AIMovementComponent.h"

Mushroom::Mushroom(CharacterSettings settings)
	:
	Character::Character(settings),
	movementComponent(new AIMovementComponent(this))
{}

Mushroom::~Mushroom()
{
	delete movementComponent;
}

void Mushroom::Update(const float deltaTime)
{
	if (IsRightFromCamera()) return;
	Character::Update(deltaTime);
}

void Mushroom::Move(const float deltaTime)
{
	movementComponent->Update();
	Character::Move(deltaTime);
}

void Mushroom::OnCharacterHit(Character* other)
{
	movementComponent->ChangeMovingDirection();
}
