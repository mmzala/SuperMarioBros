#pragma once

#include "Character.h"
#include "../Settings/MarioSettings.h"
#include "../../Engine/Graphics/Animation.h"
#include <unordered_map>

class Camera;
class MovementComponent;

enum class MarioState
{
	Dead = -1,
	Small = 0,
	Large = 1,
	Fire = 2,
};

class Mario : public Character
{
public:
	Mario(MarioSettings settings);
	~Mario() override;

	void Update(const float deltaTime) override;

protected:
	void Move(const float deltaTime) override;
	void CheckCollision(const float deltaTime) override;
	void OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition) override;
	void OnCharacterHit(Character* other) override;

private:
	void HandleHeadCollision();
	void UpdateCameraFollow();
	void UpdateAnimations();
	void UpdateState(MarioState marioState);
	DirectX::XMINT2 GetHeadCollisionTile();

private:
	Camera* camera;
	MovementComponent* movementComponent;

	MarioState marioState;
	std::unordered_map<MarioState, std::vector<Animation>> animations;
	
	// Positions are in tilemap coordinates
	std::vector<DirectX::XMINT2> headCollisionPositions;
};

