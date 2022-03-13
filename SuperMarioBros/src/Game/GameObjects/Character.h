#pragma once

#include "GameObject.h"
#include "../Settings/CharacterSettings.h"

class Animator;
class Tilemap;
class TilemapCollider;

class Character : public GameObject
{
public:
	Character(const CharacterSettings settings);
	~Character() override;

	void Update(const float deltaTime) override;

protected:
	virtual void Move(const float deltaTime);
	virtual void CheckCollision();

protected:
	Animator* animator;
	Tilemap* tilemap;
	TilemapCollider* tilemapCollider;

	DirectX::XMFLOAT2 velocity;
	float movementSpeed;
	float gravity;
};

