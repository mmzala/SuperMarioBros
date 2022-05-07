#pragma once

#include <vector>

class Scene;
class ScoreTracker;

/// <summary>
/// Manages the game itself
/// </summary>
class Game
{
public:
	Game();
	~Game();

	void Update(float deltaTime);

	/// <summary>
	/// Changes to the desired scene using the transition scene
	/// </summary>
	/// <param name="sceneIndex">: Index of the scene to load </param>
	void TransitionToScene(int sceneIndex);

	/// <summary>
	/// Chnages scene without using the transition scene
	/// </summary>
	/// <param name="sceneIndex">: Index of the scene to load </param>
	void ChangeScene(int sceneIndex);

	int GetSceneIndex();
	Scene* GetScene(int sceneIndex);
	Scene* GetCurrentScene();
	ScoreTracker* GetScoreTracker();

private:
	void ChangeScene();

private:
	std::vector<Scene*> scenes;
	int sceneIndex;
	int targetSceneIndex;
	ScoreTracker* scoreTracker;
};

struct Scenes
{
	static constexpr int MainMenu = 0;
	static constexpr int TransitionScene = 1;
	static constexpr int GameOverScene = 2;
	static constexpr int World1d1 = 3;
	static constexpr int WinScene = 4;
};

