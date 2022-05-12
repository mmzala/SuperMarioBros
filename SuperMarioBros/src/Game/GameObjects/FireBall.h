#pragma once

#include "Character.h"
#include "../../Utils/PoolableObject.h"

class FireBall : public Character, public PoolableObject
{
public:
	FireBall(CharacterSettings settings);
	~FireBall() override;

	void Update(const float deltaTime) override;
	void SetInUse(bool value) override;

protected:
	void Move(const float deltaTime) override;
	void OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition) override;
	void OnCharacterHit(Character* other) override;

private:
	void Rotate(const float deltaTime);

private:
	float rotationSpeed;
	bool resetVelocity;
};

