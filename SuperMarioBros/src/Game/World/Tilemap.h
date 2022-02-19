#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include<vector>

class Sprite;
class Transform;

class Tilemap
{
public:
	struct TilemapSettings
	{
		const char* spriteSheetFile;
		int spriteSheetSize;
		DirectX::XMFLOAT2 position;
		DirectX::XMFLOAT2 scale;

		TilemapSettings()
			:
			spriteSheetFile(nullptr),
			spriteSheetSize(0),
			position(DirectX::XMFLOAT2()),
			scale(DirectX::XMFLOAT2())
		{}
	};

public:
	Tilemap(std::vector<std::vector<int>> map, TilemapSettings settings);
	~Tilemap();

	void Draw();

private:
	/// <summary>
	/// Gets first right and left tiles in tilemap coordinates on the screen that appear in the view frustum of the camera
	/// </summary>
	/// <returns> x = most left tile that appears on screen, y = most right tile that appears on screen </returns>
	DirectX::XMINT2 GetHorizontalTilesInFrustum();

	DirectX::XMINT2 GetTilePositionInTilemapCoordinates(DirectX::XMFLOAT2 worldPosition);

private:
	std::vector<std::vector<int>> map;

	Sprite* sprite;
	Transform* transform;

	/// <summary>
	/// Size of one tile in the texture
	/// </summary>
	int tileSize;
};
