#pragma once

#include <vector>

class Scene;

/// <summary>
/// Manages the game itself
/// </summary>
class Game
{
public:
	Game();
	~Game();

	void Update(float deltaTime);

private:
	std::vector<Scene*> scenes;
	int sceneIndex;
};

