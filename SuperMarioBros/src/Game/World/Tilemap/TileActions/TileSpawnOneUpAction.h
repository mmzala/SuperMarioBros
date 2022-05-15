#pragma once

#include "../TileAction.h"

class AudioClip;

class TileSpawnOneUpAction : public TileAction
{
public:
	TileSpawnOneUpAction(std::unordered_set<DirectX::XMINT2> tilePositions);
	~TileSpawnOneUpAction() override;

	void DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition) override;

private:
	AudioClip* appearingOneUpClip;
};

