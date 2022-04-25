#pragma once

#include "../TileAction.h"

class TileCoinAction : public TileAction
{
public:
	TileCoinAction(std::unordered_set<DirectX::XMINT2> tilePositions);
	~TileCoinAction() override;

	void DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition) override;
};

