#include "Game.h"

// Scenes
#include "World/Scenes/Scene.h"
#include "World/Scenes/MainMenuScene.h"
#include "World/Scenes/World1L1.h"

// UI
#include "UI/GameplayUI.h"

Game::Game()
	:
	gameplayUI(new GameplayUI()),
	scenes(),
	sceneIndex(0),
	targetSceneIndex(sceneIndex)
{
	scenes = std::vector<Scene*>{ new MainMenuScene(), new World1L1() };
	scenes[sceneIndex]->Load();
}

Game::~Game()
{
	delete gameplayUI;

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
	gameplayUI->Update();

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

Scene* Game::GetCurrentScene()
{
	return scenes[sceneIndex];
}

void Game::ChangeScene()
{
	scenes[sceneIndex]->UnLoad();
	if (targetSceneIndex >= scenes.size()) targetSceneIndex = 0;
	sceneIndex = targetSceneIndex;
	scenes[sceneIndex]->Load();
}
