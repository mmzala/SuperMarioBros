#pragma once

#include "Character.h"
#include "../Settings/MarioSettings.h"
#include "../../Engine/Graphics/Animation.h"
#include <unordered_map>

class Camera;
class ScoreTracker;
class MovementComponent;

enum class MarioState
{
	Dead = -1,
	Controlling = 0, // Means the player can control Mario
	PowerDown = 1,
	PowerUp = 2,
	TouchedFlagPole = 3,
	InCastle = 4,
};

enum class MarioPowerState
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
	MarioState GetMarioState();
	static int GetLives();

protected:
	void Move(const float deltaTime) override;
	void CheckCollision(const float deltaTime) override;
	void OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition) override;
	void OnCharacterHit(Character* other) override;

private:
	void HandleHeadCollision();
	void UpdateCameraFollow();
	void UpdateAnimations();
	void UpdateMovementAnimations(MarioPowerState marioPowerState);
	void OnHitFlagPole(DirectX::XMFLOAT2 worldPosition, DirectX::XMINT2 tilemapPosition);
	void GoToCastle(float deltaTime);
	void PowerUpAnimation(const float deltaTime);
	void PowerDownAnimation(const float deltaTime);
	void DeathAnimation(const float deltaTime);
	void UpdateState(MarioState marioState);
	void UpdatePowerState(MarioPowerState marioPowerState);
	DirectX::XMINT2 GetHeadCollisionTile();

private:
	Camera* camera;
	ScoreTracker* scoreTracker;
	MovementComponent* movementComponent;

	static int lives;
	MarioState marioState;
	MarioPowerState marioPowerState;
	std::unordered_map<MarioPowerState, std::vector<Animation>> animations;
	
	// Positions are in tilemap coordinates
	std::vector<DirectX::XMINT2> headCollisionPositions;

	// Changing power states effects
	float poweringUpTime;
	float poweringDownTime;
	float poweringDownFlickeringSpeed;
	float powerChangeTimer;
	float powerChangeAnimationTimer;

	// Climbing down the flag pole
	float flagPoleBottomPositionY;
	float poleDescendingSpeed;
	float startPolePositionY;
	float poleDescentInterpolationValue;

	// Death animation
	float deathAnimationSpeed;
	float deathJumpSpeed;
	float deathJumpTime;
	float timeBeforeDeathAnimation;
	float timeAfterDeathBeforeSceneChange;
};

