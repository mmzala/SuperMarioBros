#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include "../../Utils/Rect.h"
#include "../../Engine/Physics/Collision.h" // Collision check and CheckSide enum
#include <functional>

class RectCollider;
class Tilemap;

class TilemapCollider
{
public:
	TilemapCollider(RectCollider* rectCollider, Tilemap* tilemap, std::function<void(CheckSide, int, DirectX::XMINT2, DirectX::XMFLOAT2)>);
	~TilemapCollider();

	void Update(DirectX::XMFLOAT2& velocity, const float deltaTime);
	CheckSide DetectedCollisions();

private:
	bool CheckSideCollision(Rect bounds, Rect vBounds, float fromPosition, float toPosition, float sidePosition, CheckSide side);
	bool CheckTileCollision(Rect bounds, DirectX::XMINT2 tilemapPosition, CheckSide side);
	DirectX::XMFLOAT2 GetCheckPosition(float positionProgress, float sidePosition, CheckSide side);

private:
	RectCollider* rectCollider;
	Tilemap* tilemap;
	CheckSide collisions;
	std::function<void(CheckSide, int, DirectX::XMINT2, DirectX::XMFLOAT2)> callback;
};

