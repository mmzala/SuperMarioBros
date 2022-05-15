#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include "../../Utils/Rect.h"
#include "../../Engine/Physics/Collision.h" // Collision check and CheckSide enum
#include <functional>

class RectBounds;
class Tilemap;

/// <summary>
/// Handles collision with the given tilemap
/// </summary>
class TilemapCollider
{
public:
	TilemapCollider(RectBounds* rectBounds, Tilemap* tilemap, std::function<void(CheckSide, int, DirectX::XMINT2, DirectX::XMFLOAT2)> callback);
	~TilemapCollider();

	void Update(DirectX::XMFLOAT2& velocity, const float deltaTime);
	bool CheckCollision(const Rect& bounds, const DirectX::XMFLOAT2& velocity, const float deltaTime);
	void CheckInvisibleBlocksCollision(DirectX::XMFLOAT2& velocity, const float deltaTime);
	CheckSide DetectedCollisions();

private:
	bool CheckSideCollision(Rect bounds, float fromPosition, float toPosition, float sidePosition, CheckSide side);
	bool CheckInvisibleSideCollision(Rect bounds, float fromPosition, float toPosition, float sidePosition, CheckSide side);
	bool CheckTileCollision(Rect bounds, DirectX::XMINT2 tilemapPosition, CheckSide side);
	bool CheckInvisibleTileCollision(Rect bounds, DirectX::XMINT2 tilemapPosition, CheckSide side);
	DirectX::XMFLOAT2 GetCheckPosition(float positionProgress, float sidePosition, CheckSide side);

private:
	RectBounds* rectBounds;
	Tilemap* tilemap;
	CheckSide collisions;
	std::function<void(CheckSide, int, DirectX::XMINT2, DirectX::XMFLOAT2)> callback;
};

