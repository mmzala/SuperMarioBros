#pragma once

#include "Scene.h"

class Game;
class Tilemap;
struct TilemapAnimation;
class GameObject;
class Canvas;

class MainMenuScene : public Scene
{
public:
	MainMenuScene(Game* game);
	~MainMenuScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	void CreateUI() override;

protected:
	Tilemap* tilemap;
	TilemapAnimation* questionMarkBlock;
	GameObject* mario;
	Canvas* mainMenuCanvas;
};

