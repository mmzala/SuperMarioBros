#include "Game.h"
#include "World/Scene.h"
#include "World/World1L1.h"

Game::Game()
	:
	scenes(),
	sceneIndex(0),
	targetSceneIndex(sceneIndex)
{
	scenes = std::vector<Scene*>{ new World1L1(), new World1L1() };
	scenes[sceneIndex]->Load();
}

Game::~Game()
{
	scenes[sceneIndex]->UnLoad();
	for (Scene* scene : scenes)
	{
		delete scene;
	}
	scenes.clear();
}

void Game::Update(float deltaTime)
{
	scenes[sceneIndex]->Update(deltaTime);

	// The ChangeScene(int) method doesn't actually change the scene, but updates targetSceneIndex, so that
	// the scene changes after it's updated. If scene would unload while it's updating we would get errors
	if (sceneIndex != targetSceneIndex)
	{
		ChangeScene();
	}
}

void Game::ChangeScene(int sceneIndex)
{
	targetSceneIndex = sceneIndex;
}

int Game::GetSceneIndex()
{
	return sceneIndex;
}

void Game::ChangeScene()
{
	scenes[sceneIndex]->UnLoad();
	if (targetSceneIndex >= scenes.size()) targetSceneIndex = 0;
	sceneIndex = targetSceneIndex;
	scenes[sceneIndex]->Load();
}
