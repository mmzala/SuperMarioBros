#pragma once

#include "Character.h"
#include "../Settings/CharacterSettings.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Graphics/Animation.h"
#include <unordered_map>

class Animator;
class Tilemap;
class TilemapCollider;
class Camera;

enum class MarioState
{
	Small = 0,
	Large = 1,
	Fire = 2,
};

class Mario : public Character
{
public:
	Mario(CharacterSettings settings);
	~Mario() override;

	void Update(const float deltaTime) override;

protected:
	void Move(const float deltaTime) override;
	void CheckCollision() override;
	void UpdateCameraFollow();
	void UpdateState(MarioState marioState);

private:
	Camera* camera;

	MarioState marioState;
	std::unordered_map<MarioState, std::vector<Animation>> animations;
};

