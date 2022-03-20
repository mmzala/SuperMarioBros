#include "Game.h"
#include "World/Scene.h"
#include "World/World1L1.h"

Game::Game()
	:
	scenes(),
	sceneIndex(0)
{
	scenes = std::vector<Scene*>{ new World1L1() };
}

Game::~Game()
{
	for (Scene* scene : scenes)
	{
		delete scene;
	}
	scenes.clear();
}

void Game::Update(float deltaTime)
{
	scenes[sceneIndex]->Update(deltaTime);
}
