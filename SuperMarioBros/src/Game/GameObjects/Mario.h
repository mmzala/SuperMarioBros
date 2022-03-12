#pragma once

#include "GameObject.h"
#include <DirectXMath.h> // XMFLOAT2

class Animator;
class Tilemap;
class TilemapCollider;
class Camera;

enum class MarioState
{
	None = 1 << 0, // None is used only at the start
	Small = 1 << 1,
	Large = 1 << 2,
	Fire = 1 << 3,
};

class Mario : public GameObject
{
public:
	Mario(SpriteSettings* spriteSettings, Tilemap* tilemap);
	~Mario() override;

	void Update(const float deltaTime) override;

private:
	void Move(DirectX::XMFLOAT2& velocity, const float deltaTime);
	void CheckCollision(DirectX::XMFLOAT2& velocity);
	void UpdateCameraFollow();
	void UpdateMarioState(MarioState marioState);

private:
	Animator* animator;
	Tilemap* tilemap;
	TilemapCollider* tilemapCollider;
	Camera* camera;

	MarioState marioState;
};

