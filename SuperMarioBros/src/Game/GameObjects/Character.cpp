#include "Character.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../World/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision

Character::Character(const CharacterSettings settings)
	:
	GameObject::GameObject(settings.spriteSettings),
	animator(new Animator(sprite)),
	tilemap(settings.tilemap),
	tilemapCollider(new TilemapCollider(collider, tilemap)),
	velocity(DirectX::XMFLOAT2(0.0f, 0.0f)),
	movementSpeed(settings.movementSpeed),
	gravity(settings.gravity)
{}

Character::~Character()
{
	delete animator;
	delete tilemapCollider;
}

void Character::Update(const float deltaTime)
{
	Move(deltaTime);
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Character::Move(const float deltaTime)
{
	CheckCollision();
	transform->position = DirectX::XMFLOAT2(transform->position.x + velocity.x, transform->position.y + velocity.y);
	velocity = DirectX::XMFLOAT2(0.0f, 0.0f); // Reset velocity
}

void Character::CheckCollision()
{
	tilemapCollider->Update(velocity);
}
