#include "Character.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../World/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../../Engine/Physics/CharacterCollider.h" // Character collision

Character::Character(const CharacterSettings settings)
	:
	GameObject::GameObject(settings.spriteSettings),
	animator(new Animator(sprite)),
	tilemap(settings.tilemap),
	tilemapCollider(new TilemapCollider(bounds, tilemap, std::bind(&Character::OnTileHit, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4))),
	characterCollider(new CharacterCollider(this, std::bind(&Character::OnCharacterHit, this, std::placeholders::_1))),
	velocity(DirectX::XMFLOAT2(0.0f, 0.0f)),
	walkingSpeed(settings.walkingSpeed),
	gravity(settings.gravity)
{}

Character::~Character()
{
	delete animator;
	delete tilemapCollider;
	delete characterCollider;
}

void Character::Update(const float deltaTime)
{
	Move(deltaTime);
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Character::Move(const float deltaTime)
{
	CheckCollision(deltaTime);
	transform->position = DirectX::XMFLOAT2(transform->position.x + velocity.x * deltaTime,
		transform->position.y + velocity.y * deltaTime);
}

void Character::CheckCollision(const float deltaTime)
{
	tilemapCollider->Update(velocity, deltaTime);
	characterCollider->Update();
}

void Character::OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition)
{}

void Character::OnCharacterHit(Character* other)
{}
