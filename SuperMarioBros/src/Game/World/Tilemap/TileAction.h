#pragma once

#include "../../../Utils/Math.h" // A vary nasty fix, Math.h is already in Tilemap.h, but then we have an error saying
// error C2908: explicit specialization; 'std::hash<DirectX::XMINT2>' has already been instantiated and
// error C2766: explicit specialization; 'std::hash<DirectX::XMINT2>' has already been defined
#include <DirectXMath.h> // XMINT2
#include <unordered_set> // Storing tile types

class Tilemap;

class TileAction
{
public:
	TileAction(std::unordered_set<DirectX::XMINT2> tilePositions);
	virtual ~TileAction();

	virtual void DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition);

	/// <summary>
	/// At what tile types should this action be fired
	/// </summary>
	/// <returns> Unordered set of tile types </returns>
	std::unordered_set<DirectX::XMINT2> GetActionTiles();

private:
	std::unordered_set<DirectX::XMINT2> actionTiles;
};

