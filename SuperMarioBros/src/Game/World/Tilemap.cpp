#include "Tilemap.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../GameObjects/Components/Transform.h"
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h"
#include <algorithm> // std::clamp

Tilemap::Tilemap(TilemapSettings settings)
	:
	tilemap(settings.tilemap),
	collisionMap(settings.collisionMap),
	sprite(new Sprite(SpriteSettings(settings.spriteSheetFile, settings.spriteSheetSize))),
	transform(new Transform(settings.position, 0.0f, settings.scale)),
	tileSizeScaled(sprite->GetSize().x * transform->scale.x) // Size of x and y will be the same anyway :)
{}

Tilemap::~Tilemap()
{
	delete sprite;
	delete transform;
}

void Tilemap::Draw()
{
	DirectX::XMFLOAT2 originalPosition = transform->position;
	DirectX::XMINT2 tilesInFrustum = GetHorizontalTilesInFrustum();

	for (int y = static_cast<int>(tilemap.size()) - 1; y > 0; y--)
	{
		for (int x = tilesInFrustum.x; x <= tilesInFrustum.y; x++)
		{
			transform->position.x = (float)(x * tileSizeScaled + originalPosition.x);

			if (tilemap[y][x] == 0) continue;
			sprite->SetFrame(tilemap[y][x]);
			sprite->Draw(transform->GetWorldMatrix());
		}

		transform->position.y += tileSizeScaled;
	}

	transform->position = originalPosition;
}

DirectX::XMFLOAT2 Tilemap::GetPositionInTilemapCoordinates(DirectX::XMFLOAT2 worldPosition)
{
	float halfTileSize = tileSizeScaled / 2;
	float topTilePosition = (tilemap.size() - static_cast<unsigned long long>(1)) * tileSizeScaled + transform->position.y;

	DirectX::XMFLOAT2 mapPosition = DirectX::XMFLOAT2();
	mapPosition.x = (worldPosition.x - transform->position.x) / tileSizeScaled;
	mapPosition.y = (topTilePosition - worldPosition.y) / tileSizeScaled;

	return mapPosition;
}

Rect Tilemap::GetTilemapBounds()
{
	Rect bounds = Rect();
	float halfTileSize = tileSizeScaled / 2;

	bounds.x = transform->position.x - halfTileSize;
	bounds.width = transform->position.x + (tileSizeScaled * tilemap[0].size()) - halfTileSize;
	bounds.y = transform->position.y - halfTileSize;
	bounds.height = transform->position.y + (tileSizeScaled * tilemap.size()) - halfTileSize;

	return bounds;
}

Rect Tilemap::GetTileBounds(DirectX::XMINT2 tilemapPosition)
{
	Rect bounds = Rect();
	float halfTileSize = tileSizeScaled / 2;
	float topTilePosition = (tilemap.size() - static_cast<unsigned long long>(1)) * tileSizeScaled + transform->position.y;

	// Calculate world position somehow
	bounds.x = tilemapPosition.x * tileSizeScaled + transform->position.x + halfTileSize;
	bounds.width = tileSizeScaled;
	bounds.y = topTilePosition - tilemapPosition.y * tileSizeScaled - halfTileSize;
	bounds.height = tileSizeScaled;

	return bounds;
}

bool Tilemap::CheckCollisionTile(DirectX::XMINT2 tilemapPosition)
{
	// Return false when under or above the map
	if ((tilemapPosition.y > collisionMap.size() - 1) ||
		tilemapPosition.y < 0)
	{
		return false;
	}

	// Return true when too far left right
	if ((tilemapPosition.x > collisionMap[0].size() - 1) || 
		tilemapPosition.x < 0)
	{
		return true;
	}

	return collisionMap[tilemapPosition.y][tilemapPosition.x];
}

DirectX::XMINT2 Tilemap::GetHorizontalTilesInFrustum()
{
	Rect viewportBounds = SMBEngine::GetInstance()->GetCamera()->GetViewportBounds();

	// Adding tileSizeScaled to right coordinate, to prevent player from seeing any artifacts when going fast
	DirectX::XMFLOAT2 worldPosition = DirectX::XMFLOAT2(viewportBounds.x,
		viewportBounds.width + tileSizeScaled);

	// Both x and y are horizontal coordinates in this case
	DirectX::XMINT2 mapPosition = DirectX::XMINT2();
	mapPosition.x = static_cast<int32_t>((worldPosition.x - transform->position.x) / tileSizeScaled);
	mapPosition.y = static_cast<int32_t>((worldPosition.y - transform->position.x) / tileSizeScaled);

	mapPosition.x = std::clamp(mapPosition.x, 0, (int)tilemap[0].size() - 1);
	mapPosition.y = std::clamp(mapPosition.y, 0, (int)tilemap[0].size() - 1);

	return mapPosition;
}
