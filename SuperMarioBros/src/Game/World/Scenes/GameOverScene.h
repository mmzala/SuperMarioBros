#pragma once

#include "Scene.h"

class Game;
class DXManager;
class Canvas;

class GameOverScene : public Scene
{
public:
	GameOverScene(Game* game);
	~GameOverScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	void CreateUI() override;

private:
	DXManager* graphics;
	Canvas* canvas;

	float timeToTransition;
};

