#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include "../../Utils/Rect.h"
#include <vector>
#include "../../Engine/Graphics/Animation.h"
#include <unordered_map>

class Sprite;
class Transform;

struct TilemapAnimation : Animation
{
	float timer;

	TilemapAnimation(int startFrame = 0, int endFrame = 0, float speed = 0.0f)
		:
		Animation::Animation(startFrame, endFrame, speed),
		timer(0.0f)
	{}
};

struct TilemapSettings
{
	std::vector<std::vector<int>> tilemap;
	std::vector<std::vector<bool>> collisionMap;
	const char* spriteSheetFile;
	DirectX::XMINT2 spriteSheetSize;
	std::vector<TilemapAnimation*> animations;
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 scale;

	TilemapSettings()
		:
		tilemap(),
		collisionMap(),
		spriteSheetFile(nullptr),
		spriteSheetSize(DirectX::XMINT2()),
		animations(),
		position(DirectX::XMFLOAT2()),
		scale(DirectX::XMFLOAT2())
	{}
};

class Tilemap
{
public:
	Tilemap(TilemapSettings settings);
	~Tilemap();

	void Update(const float deltaTime);

	/// <summary>
	/// Calculates position in tilemap coordinates
	/// </summary>
	/// <param name="worldPosition">: Position in the world </param>
	/// <returns> Position in tilemap coordinates </returns>
	DirectX::XMFLOAT2 GetPositionInTilemapCoordinates(DirectX::XMFLOAT2 worldPosition);

	/// <summary>
	/// Calculates position in wold coordinates
	/// </summary>
	/// <param name="tilemapPosition">: Position in the tilemap </param>
	/// <returns> Position in world coortinates </returns>
	DirectX::XMFLOAT2 GetPositionInWorldCoordinates(DirectX::XMINT2 tilemapPosition);

	/// <summary>
	/// Gets the bounds of the tilemap
	/// </summary>
	/// <returns>Bounds of the tilemap</returns>
	Rect GetTilemapBounds();

	/// <summary>
	/// Gets the bounds of a tile with already applied position
	/// </summary>
	/// <param name="tilemapPosition">: Position in tilemap coordinates </param>
	/// <returns> Bounds of a tile </returns>
	Rect GetTileBounds(DirectX::XMINT2 tilemapPosition);

	/// <summary>
	/// Gets already scaled size of a normal tile in this tilemap.
	/// Because the tiles are squares, both axis are the same size
	/// </summary>
	/// <returns> Size of a tile </returns>
	float GetTileSize();

	/// <summary>
	/// Checks if the tile has collision. Also returns true when position is outside collisionMap
	/// </summary>
	/// <param name="tilemapPosition">: Position in tilemap coordinates </param>
	/// <returns> If the tile has collision </returns>
	bool CheckCollisionTile(DirectX::XMINT2 tilemapPosition);

	/// <summary>
	/// Return what tile it is
	/// </summary>
	/// <param name="tilemapPsoition">: Position in tilemap coordinates </param>
	/// <returns> What type a tile is </returns>
	int GetTileType(DirectX::XMINT2 tilemapPosition);
	void BreakTile(DirectX::XMINT2 tilemapPosition);

private:
	/// <summary>
	/// Gets first right and left tiles in tilemap coordinates on the screen that appear in the view frustum of the camera
	/// </summary>
	/// <returns> x = most left tile that appears on screen, y = most right tile that appears on screen </returns>
	DirectX::XMINT2 GetHorizontalTilesInFrustum();
	bool IsPositionOutOfBounds(DirectX::XMINT2 tilemapPosition);
	void Draw();
	void UpdateAnimations(const float deltaTime);

private:
	std::vector<std::vector<int>> tilemap;
	std::vector<std::vector<bool>> collisionMap;

	Sprite* sprite;
	Transform* transform;

	/// <summary>
	/// Size of one tile in the texture, with already applied transform->size
	/// </summary>
	float tileSizeScaled;

	std::unordered_map<int, TilemapAnimation*> animations;
	std::vector<DirectX::XMINT2> tilesToAnimate;
};
