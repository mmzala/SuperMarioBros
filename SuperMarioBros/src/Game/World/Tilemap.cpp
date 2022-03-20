#include "Tilemap.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../GameObjects/Components/Transform.h"
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h"
#include <algorithm> // std::clamp / std::find
#include "../../Utils/Math.h" // FindInVector

Tilemap::Tilemap(TilemapSettings settings)
	:
	tilemap(settings.tilemap),
	collisionMap(settings.collisionMap),
	sprite(new Sprite(SpriteSettings(settings.spriteSheetFile, settings.spriteSheetSize))),
	transform(new Transform(settings.position, 0.0f, settings.scale)),
	tileSizeScaled(sprite->GetSize().x * transform->scale.x), // Size of x and y will be the same anyway :)
	animations(),
	tilesToAnimate()
{
	// Setup animations in unordered_map
	for (int animation = 0; animation < settings.animations.size(); animation++)
	{
		for (int animationFrame = settings.animations[animation]->startFrame; 
			animationFrame < settings.animations[animation]->endFrame + 1; animationFrame++)
		{
			animations.insert(std::pair<int, TilemapAnimation*>(animationFrame, settings.animations[animation]));
		}
	}

	// Cache tiles to be animated
	for (int y = static_cast<int>(tilemap.size()) - 1; y > 0; y--)
	{
		for (int x = 0; x < tilemap[0].size(); x++)
		{
			if (animations.count(tilemap[y][x])) tilesToAnimate.push_back(DirectX::XMINT2(x, y));
		}
	}
}

Tilemap::~Tilemap()
{
	delete sprite;
	delete transform;
}

void Tilemap::Update(const float deltaTime)
{
	UpdateAnimations(deltaTime);
	Draw();

	// Reset animation timers if needed
	for (std::unordered_map<int, TilemapAnimation*>::iterator iterator = animations.begin(); iterator != animations.end(); iterator++)
	{
		TilemapAnimation* anim = iterator->second;
		if (anim->timer > 1.0f) anim->timer = 0.0f;
	}
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

DirectX::XMFLOAT2 Tilemap::GetPositionInWorldCoordinates(DirectX::XMINT2 tilemapPosition)
{
	DirectX::XMFLOAT2 position = DirectX::XMFLOAT2();
	float topTilePosition = (tilemap.size() - static_cast<unsigned long long>(1)) * tileSizeScaled + transform->position.y;
	
	position.x = tilemapPosition.x * tileSizeScaled + transform->position.x;
	position.y = topTilePosition - tilemapPosition.y * tileSizeScaled;

	return position;
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

	bounds.x = tilemapPosition.x * tileSizeScaled + transform->position.x + halfTileSize;
	bounds.width = tileSizeScaled;
	bounds.y = topTilePosition - tilemapPosition.y * tileSizeScaled - halfTileSize;
	bounds.height = tileSizeScaled;

	return bounds;
}

float Tilemap::GetTileSize()
{
	return tileSizeScaled;
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

int Tilemap::GetTileType(DirectX::XMINT2 tilemapPosition)
{
	if (IsPositionOutOfBounds(tilemapPosition)) return 0;
	return tilemap[tilemapPosition.y][tilemapPosition.x];
}

void Tilemap::BreakTile(DirectX::XMINT2 tilemapPosition)
{
	if (IsPositionOutOfBounds(tilemapPosition)) return;

	// If tile is an animated tile, then remove it from tilesToAnimate
	std::pair<bool, int> foundAnimatedTile = Math::FindInVector(tilesToAnimate, tilemapPosition);
	if (foundAnimatedTile.first) tilesToAnimate.erase(tilesToAnimate.begin() + foundAnimatedTile.second);

	tilemap[tilemapPosition.y][tilemapPosition.x] = 0;
	collisionMap[tilemapPosition.y][tilemapPosition.x] = false;
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

bool Tilemap::IsPositionOutOfBounds(DirectX::XMINT2 tilemapPosition)
{
	if ((tilemapPosition.x > collisionMap[0].size() - 1) ||
		tilemapPosition.x < 0 ||
		(tilemapPosition.y > collisionMap.size() - 1) ||
		tilemapPosition.y < 0)
	{
		return true;
	}

	return false;
}

void Tilemap::Draw()
{
	DirectX::XMFLOAT2 originalPosition = transform->position;
	DirectX::XMINT2 tilesInFrustum = GetHorizontalTilesInFrustum();

	for (int y = static_cast<int>(tilemap.size()) - 1; y > 0; y--)
	{
		for (int x = tilesInFrustum.x; x <= tilesInFrustum.y; x++)
		{
			if (tilemap[y][x] == 0) continue;

			transform->position.x = (float)(x * tileSizeScaled + originalPosition.x);
			sprite->SetFrame(tilemap[y][x]);
			sprite->Draw(transform->GetWorldMatrix());
		}

		transform->position.y += tileSizeScaled;
	}

	transform->position = originalPosition;
}

void Tilemap::UpdateAnimations(const float deltaTime)
{
	for (std::unordered_map<int, TilemapAnimation*>::iterator iterator = animations.begin(); iterator != animations.end(); iterator++)
	{
		TilemapAnimation* anim = iterator->second;
		anim->timer += anim->speed * deltaTime;
	}

	for (DirectX::XMINT2 tile : tilesToAnimate)
	{
		TilemapAnimation* animation = animations[tilemap[tile.y][tile.x]];
		if (animation->timer > 1.0f)
		{
			tilemap[tile.y][tile.x]++;
			if (tilemap[tile.y][tile.x] > animation->endFrame)
			{
				tilemap[tile.y][tile.x] = animation->startFrame;
			}
		}
	}
}
