#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include <Windows.h> // RECT
#include<vector>

class Sprite;
class Transform;

struct TilemapSettings
{
	std::vector<std::vector<int>> tilemap;
	std::vector<std::vector<bool>> collisionMap;
	const char* spriteSheetFile;
	int spriteSheetSize;
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 scale;

	TilemapSettings()
		:
		tilemap(),
		collisionMap(),
		spriteSheetFile(nullptr),
		spriteSheetSize(0),
		position(DirectX::XMFLOAT2()),
		scale(DirectX::XMFLOAT2())
	{}
};

class Tilemap
{
public:
	Tilemap(TilemapSettings settings);
	~Tilemap();

	void Draw();

	/// <summary>
	/// Calculates position in tilemap coordinates
	/// </summary>
	/// <param name="worldPosition">: Position in the world </param>
	/// <returns> Position in tilemap coordinates </returns>
	DirectX::XMFLOAT2 GetPositionInTilemapCoordinates(DirectX::XMFLOAT2 worldPosition);

	/// <summary>
	/// Gets the bounds of a tile with already applied position
	/// </summary>
	/// <param name="tilemapPosition">: Position in tilemap coordinates </param>
	/// <returns> Bounds of a tile </returns>
	RECT GetTileBounds(DirectX::XMINT2 tilemapPosition);

	/// <summary>
	/// Checks if the tile has collision. Also returns true when position is outside collisionMap
	/// </summary>
	/// <param name="tilemapPosition">: Position in tilemap coordinates </param>
	/// <returns> If the tile has collision </returns>
	bool CheckCollisionTile(DirectX::XMINT2 tilemapPosition);

private:
	/// <summary>
	/// Gets first right and left tiles in tilemap coordinates on the screen that appear in the view frustum of the camera
	/// </summary>
	/// <returns> x = most left tile that appears on screen, y = most right tile that appears on screen </returns>
	DirectX::XMINT2 GetHorizontalTilesInFrustum();

private:
	std::vector<std::vector<int>> tilemap;
	std::vector<std::vector<bool>> collisionMap;

	Sprite* sprite;
	Transform* transform;

	/// <summary>
	/// Size of one tile in the texture, with already applied transform->size
	/// </summary>
	int tileSizeScaled;
};
