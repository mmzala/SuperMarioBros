#pragma once

#include <vector>

class Scene;
class GameplayUI;

/// <summary>
/// Manages the game itself
/// </summary>
class Game
{
public:
	Game();
	~Game();

	void Update(float deltaTime);
	void ChangeScene(int sceneIndex);
	int GetSceneIndex();

public:
	GameplayUI* gameplayUI;

private:
	void ChangeScene();

private:
	std::vector<Scene*> scenes;
	int sceneIndex;
	int targetSceneIndex;
};

