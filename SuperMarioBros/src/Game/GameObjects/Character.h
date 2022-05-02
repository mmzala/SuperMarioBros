#pragma once

#include "GameObject.h"
#include "../Settings/CharacterSettings.h"
#include "../../Engine/Physics/Collision.h" // Checkside

class Animator;
class Tilemap;
class TilemapCollider;
class CharacterCollider;

class Character : public GameObject
{
	friend class MovementComponent;
	friend class AIMovementComponent;
	friend class CharacterCollider;

public:
	Character(const CharacterSettings settings);
	~Character() override;

	void Update(const float deltaTime) override;

	/// <summary>
	/// Gets the position that can be used to place the character directly on a tile.
	/// Use one tile above the the tile the character has to stand on.
	/// </summary>
	/// <param name="tilemapPosition">: Position in tilemap coordinates </param>
	/// <returns> Position that the character can stand on a tile </returns>
	DirectX::XMFLOAT2 GetSpawnPositionOnTile(DirectX::XMINT2 tilemapPosition);
	DirectX::XMFLOAT2 GetVelocity();

protected:
	virtual void Move(const float deltaTime);
	virtual void CheckCollision(const float deltaTime);
	virtual void OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition);
	virtual void OnCharacterHit(Character* other);

protected:
	Animator* animator;
	Tilemap* tilemap;
	TilemapCollider* tilemapCollider;
	CharacterCollider* characterCollider;

	DirectX::XMFLOAT2 velocity;
	float walkingSpeed;
	float gravity;
};

