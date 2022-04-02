#include "Goomba.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../../Engine/Physics/RectBounds.h" // Collision
#include "../World/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../Data/Animations.h" // Animations data

Goomba::Goomba(CharacterSettings settings)
	:
	Character::Character(settings),
	goombaState(GoombaState::None),
	animations(Animations::Goomba::goomba),
	walkingRight(false)
{
	UpdateState(GoombaState::Walking);
	animator->SetAnimation(animations[Animations::Goomba::AnimationState::Walking]);
}

Goomba::~Goomba()
{}

void Goomba::Update(const float deltaTime)
{
	if(goombaState == GoombaState::Walking) Move(deltaTime);
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Goomba::Move(const float deltaTime)
{
	velocity.y = -gravity;
	velocity.x = walkingSpeed * (walkingRight ? 1 : -1);

	Character::Move(deltaTime);
}

void Goomba::CheckCollision(const float deltaTime)
{
	Character::CheckCollision(deltaTime);

	// If velocity is 0 that means we hit something, so we change direction
	if (velocity.x == 0.0f) walkingRight = !walkingRight;
}

void Goomba::UpdateState(GoombaState state)
{
	if (this->goombaState == state) return;
	this->goombaState = state;
}
