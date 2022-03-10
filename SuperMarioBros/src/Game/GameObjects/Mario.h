#pragma once

#include "GameObject.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Physics/Rect.h"
#include "../../Engine/Physics/Collision.h" // Collision check and CheckSide enum

class Tilemap;
class Camera;

class Mario : public GameObject
{
public:
	Mario(SpriteSettings* spriteSettings, Tilemap* tilemap);
	~Mario() override;

	void Update(const float deltaTime) override;

private:
	void Move(DirectX::XMFLOAT2& velocity, const float deltaTime);
	void CheckCollision(DirectX::XMFLOAT2& velocity);
	bool CheckTileCollision(Rect bounds, DirectX::XMFLOAT2 fTilemapPosition, CheckSide side);

private:
	Tilemap* tilemap;
	Camera* camera;
};

