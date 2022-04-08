#pragma once

#include "GameplayScene.h"

class Game;
class TileAction;
struct TilemapAnimation;

class World1L1 : public GameplayScene
{
public:
	World1L1(Game* game);
	~World1L1() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	void CreateUI() override;

protected:
	TilemapAnimation* questionMarkBlock;
	TileAction* spawnPowerUpAction;
};

