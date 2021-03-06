#pragma once

#include "../TileAction.h"

class AudioClip;

class TileSpawnPowerUpAction : public TileAction
{
public:
	TileSpawnPowerUpAction(std::unordered_set<DirectX::XMINT2> tilePositions);
	~TileSpawnPowerUpAction() override;

	void DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition) override;

private:
	AudioClip* appearingPowerUpClip;
};

