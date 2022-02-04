#pragma once

class GameObject;

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
	GameObject* object;
	GameObject* object2;
};

