#pragma once

class GameObject;
class Tilemap;

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

	Tilemap* tilemap;

	float playerX;
	float playerY;
};

