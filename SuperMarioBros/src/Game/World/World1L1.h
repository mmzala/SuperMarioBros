#pragma once

#include "Scene.h"

struct TilemapAnimation;
class Text;
class UISprite;
class Canvas;

class World1L1 : public Scene
{
public:
	World1L1();
	~World1L1() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	void CreateUI() override;

protected:
	TilemapAnimation* questionMarkBlock;

	Canvas* canvas;
	Text* marioText;
	Text* scoreText;
	Text* coinCountText;
	Text* worldText;
	Text* worldCountText;
	Text* timeText;
	Text* timeCountText;
	UISprite* coinSprite;
};

