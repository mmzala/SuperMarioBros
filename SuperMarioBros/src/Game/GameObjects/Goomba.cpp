#include "Goomba.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../../Engine/Physics/RectCollider.h" // Collision
#include "../World/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../Data/Animations.h" // Animations data

Goomba::Goomba(SpriteSettings* spriteSettings, Tilemap* tilemap)
	:
	GameObject::GameObject(spriteSettings),
	animator(new Animator(sprite)),
	tilemap(tilemap),
	tilemapCollider(new TilemapCollider(collider, tilemap)),
	goombaState(GoombaState::None),
	animations(Animations::Goomba::goomba),
	walkingRight(false)
{
	UpdateState(GoombaState::Walking);
	animator->SetAnimation(animations[Animations::Goomba::AnimationState::Walking]);
}

Goomba::~Goomba()
{
	delete animator;
	delete tilemapCollider;
}

void Goomba::Update(const float deltaTime)
{
	DirectX::XMFLOAT2 velocity = DirectX::XMFLOAT2();
	if(goombaState == GoombaState::Walking) Move(velocity, deltaTime);

	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Goomba::Move(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	constexpr float gravity = 150.0f;
	constexpr float movementSpeed = 150.0f;

	velocity.y -= gravity * deltaTime;
	velocity.x += movementSpeed * (walkingRight ? -1 : 1) * deltaTime;

	tilemapCollider->Update(velocity);
	// If velocity is 0 that means we hit something, so we change direction
	if (velocity.x == 0.0f) walkingRight = !walkingRight;
	transform->position = DirectX::XMFLOAT2(transform->position.x + velocity.x, transform->position.y + velocity.y);
}

void Goomba::UpdateState(GoombaState state)
{
	if (this->goombaState == state) return;
	this->goombaState = state;
}
