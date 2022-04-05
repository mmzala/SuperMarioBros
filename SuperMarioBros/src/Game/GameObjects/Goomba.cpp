#include "Goomba.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../../Engine/Physics/RectBounds.h" // Collision
#include "../World/Tilemap/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../Data/Animations.h" // Animations data
#include "Components/AIMovementComponent.h"

Goomba::Goomba(CharacterSettings settings)
	:
	Character::Character(settings),
	movementComponent(new AIMovementComponent(this)),
	goombaState(GoombaState::None),
	animations(Animations::Goomba::goomba)
{
	UpdateState(GoombaState::Walking);
	animator->SetAnimation(animations[Animations::Goomba::AnimationState::Walking]);
}

Goomba::~Goomba()
{
	delete movementComponent;
}

void Goomba::Update(const float deltaTime)
{
	if (IsRightFromCamera()) return;
	if(goombaState == GoombaState::Walking) Move(deltaTime);
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Goomba::Move(const float deltaTime)
{
	movementComponent->Update();
	Character::Move(deltaTime);
}

void Goomba::CheckCollision(const float deltaTime)
{
	Character::CheckCollision(deltaTime);
}

void Goomba::UpdateState(GoombaState state)
{
	if (this->goombaState == state) return;
	this->goombaState = state;
}
