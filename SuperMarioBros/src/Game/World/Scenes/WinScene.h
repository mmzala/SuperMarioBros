#pragma once

#include "Scene.h"

class Game;
class DXManager;
class Canvas;
class AudioClip;

class WinScene : public Scene
{
public:
	WinScene(Game* game);
	~WinScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	void CreateUI() override;

private:
	DXManager* graphics;
	Canvas* canvas;
	AudioClip* winClip;
};

