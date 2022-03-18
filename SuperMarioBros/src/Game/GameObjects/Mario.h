#pragma once

// Movement physics credits:
// https://web.archive.org/web/20130807122227/http://i276.photobucket.com/albums/kk21/jdaster64/smb_playerphysics.png

#include "Character.h"
#include "../Settings/MarioSettings.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Graphics/Animation.h"
#include <unordered_map>

class Animator;
class Tilemap;
class TilemapCollider;
class Camera;

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
	void MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const float deltaTime);
	void CheckCollision(const float deltaTime) override;
	void UpdateCameraFollow();
	void UpdateState(MarioState marioState);

private:
	Camera* camera;

	MarioState marioState;
	std::unordered_map<MarioState, std::vector<Animation>> animations;

	// Movement variables
	float runningSpeed;
	float walkingAcceleration;
	float runningAcceleration;
	float releaseDeceleration;
	float skiddingDeceleration;
	float skidTurnaroundSpeed;
	float runningDecelerationDelay;
	float runningDecelerationTimer;
};

