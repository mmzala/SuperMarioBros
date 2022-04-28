#pragma once

#include <vector>

class Scene;
class ScoreTracker;
class AudioClip;

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
	Scene* GetCurrentScene();
	ScoreTracker* GetScoreTracker();

private:
	void ChangeScene();

private:
	std::vector<Scene*> scenes;
	int sceneIndex;
	int targetSceneIndex;
	ScoreTracker* scoreTracker;

	AudioClip* clip;
};

