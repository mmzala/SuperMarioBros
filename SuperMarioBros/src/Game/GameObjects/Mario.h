#pragma once

#include "Character.h"
#include "../Settings/MarioSettings.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Graphics/Animation.h"
#include <unordered_map>

class Animator;
class Tilemap;
class TilemapCollider;
class Camera;
class MovementComponent;

enum class MarioState
{
	None = -1, // Only used when starting game
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
	void UpdateCameraFollow();
	void UpdateState(MarioState marioState);

private:
	Camera* camera;
	MovementComponent* movementComponent;

	MarioState marioState;
	std::unordered_map<MarioState, std::vector<Animation>> animations;
};

