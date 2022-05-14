#pragma once

#include "Character.h"
#include "../../Utils/PoolableObject.h"

class ScoreTracker;

class FireBall : public Character, public PoolableObject
{
public:
	FireBall(CharacterSettings settings);
	~FireBall() override;

	void Update(const float deltaTime) override;
	void SetTravelingDirection(bool right);
	void SetInUse(bool value) override;

protected:
	void Move(const float deltaTime) override;
	void OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition) override;
	void OnCharacterHit(Character* other) override;

private:
	void Rotate(const float deltaTime);

private:
	ScoreTracker* scoreTracker;

	float rotationSpeed;
	bool travelingDirection; // true = right / false = left
	bool resetVelocity;
};

