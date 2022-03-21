#pragma once

#include "Scene.h"

struct TilemapAnimation;

class World1L1 : public Scene
{
public:
	World1L1();
	~World1L1() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	TilemapAnimation* questionMarkBlock;
};

