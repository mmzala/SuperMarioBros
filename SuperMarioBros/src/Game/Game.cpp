#include "Game.h"

// Scenes
#include "World/Scenes/Scene.h"
#include "World/Scenes/MainMenuScene.h"
#include "World//Scenes/TransitionScene.h"
#include "World/Scenes/GameOverScene.h"
#include "World/Scenes/WinScene.h"
#include "World/Scenes/World1L1.h"

// Scoring
#include "Scoring/ScoreTracker.h"

Game::Game()
	:
	scenes(),
	sceneIndex(0),
	targetSceneIndex(sceneIndex),
	scoreTracker(new ScoreTracker(this, 50.0f))
{
	scenes = std::vector<Scene*>{ new MainMenuScene(this), new TransitionScene(this), 
		new GameOverScene(this), new World1L1(this), new WinScene(this) };
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

	delete scoreTracker;
}

void Game::Update(float deltaTime)
{
	scenes[sceneIndex]->Update(deltaTime);
	scoreTracker->Update(deltaTime);

	// The ChangeScene(int) method doesn't actually change the scene, but updates targetSceneIndex, so that
	// the scene changes after it's updated. If scene would unload while it's updating we would get errors
	if (sceneIndex != targetSceneIndex)
	{
		ChangeScene();
	}
}

void Game::TransitionToScene(int sceneIndex)
{
	TransitionScene* scene = static_cast<TransitionScene*>(scenes[Scenes::TransitionScene]);
	scene->SetSceneToTransitionTo(sceneIndex);
	targetSceneIndex = Scenes::TransitionScene;
}

void Game::ChangeScene(int sceneIndex)
{
	targetSceneIndex = sceneIndex;
}

int Game::GetSceneIndex()
{
	return sceneIndex;
}

Scene* Game::GetScene(int sceneIndex)
{
	return scenes[sceneIndex];
}

Scene* Game::GetCurrentScene()
{
	return scenes[sceneIndex];
}

ScoreTracker* Game::GetScoreTracker()
{
	return scoreTracker;
}

void Game::ChangeScene()
{
	scenes[sceneIndex]->UnLoad();
	if (targetSceneIndex >= scenes.size()) targetSceneIndex = 0;
	sceneIndex = targetSceneIndex;
	scenes[sceneIndex]->Load();
}
