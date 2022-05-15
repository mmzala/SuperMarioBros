#include "TilemapCollider.h"
#include "RectBounds.h"
#include "../../Game/World/Tilemap/Tilemap.h"
#include "../../Utils/Math.h" // Lerp / * operator overload
// lerp is only included in C++20, but then I would need to rewrite my world collision vector initialization, so no thanks :)
#include <cmath> // floor / ceil

TilemapCollider::TilemapCollider(RectBounds* rectBounds, Tilemap* tilemap, std::function<void(CheckSide, int, DirectX::XMINT2, DirectX::XMFLOAT2)> callback)
	:
	rectBounds(rectBounds),
	tilemap(tilemap),
	collisions(),
	callback(callback)
{}

TilemapCollider::~TilemapCollider()
{}

void TilemapCollider::Update(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	Rect bounds = rectBounds->GetBounds();
	DirectX::XMFLOAT2 deltaVelocity = DirectX::XMFLOAT2(velocity * deltaTime);
	deltaVelocity.y -= 0.01f; // Sometimes Mario would get stuck after jumping, but subtracting 0.01f fixed it :)
	Rect vBounds = rectBounds->GetBoundsWithPositionOffset(deltaVelocity);

	bool collidedBottom = CheckSideCollision(vBounds, bounds.x, bounds.x + bounds.width, vBounds.y, CheckSide::Bottom);
	bool collidedTop = CheckSideCollision(vBounds, bounds.x, bounds.x + bounds.width, vBounds.y + vBounds.height, CheckSide::Top);
	if (collidedBottom || collidedTop)
	{
		velocity.y = 0.0f;
	}

	bool collidedLeft = CheckSideCollision(vBounds, bounds.y, bounds.y + bounds.height, vBounds.x, CheckSide::Left);
	bool collidedRight = CheckSideCollision(vBounds, bounds.y, bounds.y + bounds.height, vBounds.x + vBounds.width, CheckSide::Right);
	if (collidedLeft || collidedRight)
	{
		velocity.x = 0.0f;
	}

	CheckSide sidesDetected{};
	if (collidedBottom) sidesDetected |= CheckSide::Bottom;
	if (collidedTop) sidesDetected |= CheckSide::Top;
	if (collidedLeft) sidesDetected |= CheckSide::Left;
	if (collidedRight) sidesDetected |= CheckSide::Right;
	collisions = sidesDetected;
}

bool TilemapCollider::CheckCollision(const Rect& bounds, const DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	DirectX::XMFLOAT2 deltaVelocity = DirectX::XMFLOAT2(velocity * deltaTime);
	Rect vBounds = rectBounds->GetBoundsWithPositionOffset(deltaVelocity);

	if(CheckSideCollision(vBounds, bounds.x, bounds.x + bounds.width, vBounds.y, CheckSide::Bottom) ||
		CheckSideCollision(vBounds, bounds.x, bounds.x + bounds.width, vBounds.y + vBounds.height, CheckSide::Top) ||
		CheckSideCollision(vBounds, bounds.y, bounds.y + bounds.height, vBounds.x, CheckSide::Left) ||
		CheckSideCollision(vBounds, bounds.y, bounds.y + bounds.height, vBounds.x + vBounds.width, CheckSide::Right))
	{
		return true;
	}

	return false;
}

void TilemapCollider::CheckInvisibleBlocksCollision(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	Rect bounds = rectBounds->GetBounds();
	DirectX::XMFLOAT2 deltaVelocity = DirectX::XMFLOAT2(velocity * deltaTime);
	Rect vBounds = rectBounds->GetBoundsWithPositionOffset(deltaVelocity);

	// Make sure we only hit the tile from the bottom
	if (!CheckInvisibleSideCollision(bounds, bounds.x, bounds.x + bounds.width, bounds.y + bounds.height, CheckSide::Top, false) &&
		!CheckInvisibleSideCollision(vBounds, bounds.y, bounds.y + bounds.height, vBounds.x, CheckSide::Left, false) &&
		!CheckInvisibleSideCollision(vBounds, bounds.y, bounds.y + bounds.height, vBounds.x + vBounds.width, CheckSide::Right, false) &&
		!CheckInvisibleSideCollision(vBounds, bounds.x, bounds.x + bounds.width, vBounds.y, CheckSide::Bottom, false) &&
		CheckInvisibleSideCollision(vBounds, bounds.x, bounds.x + bounds.width, vBounds.y + vBounds.height, CheckSide::Top, true))
	{
		velocity.y = 0.0f;
		collisions |= CheckSide::Top;
	}
}

CheckSide TilemapCollider::DetectedCollisions()
{
	return collisions;
}

bool TilemapCollider::CheckSideCollision(Rect bounds, float fromPosition, float toPosition, float sidePosition, CheckSide side)
{
	float tileSize = tilemap->GetTileSize();
	int iterations = static_cast<int>((toPosition - fromPosition) / tileSize); // Calculate how many checks it takes to check for all tiles that can be in proximity
	iterations += 2; // We always want to check atleast the corners
	bool hit = false;

	for (int i = 0; i < iterations; i++)
	{
		float checkProgress = static_cast<float>(i) / (iterations - 1);
		float positionProgress = Math::Lerp(fromPosition, toPosition, checkProgress);
		DirectX::XMFLOAT2 checkPosition = GetCheckPosition(positionProgress, sidePosition, side);
		DirectX::XMFLOAT2 fTilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
		DirectX::XMINT2 tilemapPosition = DirectX::XMINT2((int32_t)std::round(fTilemapPosition.x), (int32_t)std::round(fTilemapPosition.y));

		if (CheckTileCollision(bounds, tilemapPosition, side))
		{
			callback(side, tilemap->GetTileType(tilemapPosition), tilemapPosition, checkPosition);
			hit = true;
		}
	}

	return hit;
}

bool TilemapCollider::CheckInvisibleSideCollision(Rect bounds, float fromPosition, float toPosition, float sidePosition, CheckSide side, bool callCallback)
{
	float tileSize = tilemap->GetTileSize();
	int iterations = static_cast<int>((toPosition - fromPosition) / tileSize); // Calculate how many checks it takes to check for all tiles that can be in proximity
	iterations += 2; // We always want to check atleast the corners
	bool hit = false;

	for (int i = 0; i < iterations; i++)
	{
		float checkProgress = static_cast<float>(i) / (iterations - 1);
		float positionProgress = Math::Lerp(fromPosition, toPosition, checkProgress);
		DirectX::XMFLOAT2 checkPosition = GetCheckPosition(positionProgress, sidePosition, side);
		DirectX::XMFLOAT2 fTilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
		DirectX::XMINT2 tilemapPosition = DirectX::XMINT2((int32_t)std::round(fTilemapPosition.x), (int32_t)std::round(fTilemapPosition.y));

		if (CheckInvisibleTileCollision(bounds, tilemapPosition, side))
		{
			if (callCallback)
			{
				callback(side, tilemap->GetTileType(tilemapPosition), tilemapPosition, checkPosition);
			}
			hit = true;
		}
	}

	return hit;
}

bool TilemapCollider::CheckTileCollision(Rect bounds, DirectX::XMINT2 tilemapPosition, CheckSide side)
{
	if (!tilemap->CheckCollisionTile(tilemapPosition)) return false;
	return Collision::TilemapCheck(tilemap->GetTileBounds(tilemapPosition), bounds, side);
}

bool TilemapCollider::CheckInvisibleTileCollision(Rect bounds, DirectX::XMINT2 tilemapPosition, CheckSide side)
{
	if (!tilemap->CheckInvisibleCollisionTile(tilemapPosition)) return false;
	return Collision::TilemapCheck(tilemap->GetTileBounds(tilemapPosition), bounds, side);
}

DirectX::XMFLOAT2 TilemapCollider::GetCheckPosition(float positionProgress, float sidePosition, CheckSide side)
{
	switch (side)
	{
	case CheckSide::Top:
	case CheckSide::Bottom:
		return DirectX::XMFLOAT2(positionProgress, sidePosition);
		break;
	case CheckSide::Right:
	case CheckSide::Left:
		return DirectX::XMFLOAT2(sidePosition, positionProgress);
		break;
	}

	return DirectX::XMFLOAT2();
}
