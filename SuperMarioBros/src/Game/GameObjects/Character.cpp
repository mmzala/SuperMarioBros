#include "Character.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../World/Tilemap/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../../Engine/Physics/CharacterCollider.h" // Character collision
#include "../../Engine/Physics/RectBounds.h" // Calculating position on a tile to stand on

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
	gravity(settings.gravity),
	gravityAcceleration(settings.gravityAcceleration)
{}

Character::~Character()
{
	delete animator;
	delete tilemapCollider;
	delete characterCollider;
}

void Character::Update(const float deltaTime)
{
	CheckFalledOffMap(true);
	Move(deltaTime);
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

DirectX::XMFLOAT2 Character::GetSpawnPositionOnTile(DirectX::XMINT2 tilemapPosition)
{
	DirectX::XMFLOAT2 position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	Rect bounds = this->bounds->GetBounds();
	position.y += bounds.height;

	return position;
}

DirectX::XMFLOAT2 Character::GetVelocity()
{
	return velocity;
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
	characterCollider->Update(deltaTime);
}

void Character::OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition)
{}

void Character::OnCharacterHit(Character* other)
{}

bool Character::CheckFalledOffMap(bool deactivateCharacter)
{
	constexpr float minPositionY = -150.0f;
	if (transform->position.y < minPositionY)
	{
		if (deactivateCharacter) isActive = false;
		return true;
	}

	return false;
}
