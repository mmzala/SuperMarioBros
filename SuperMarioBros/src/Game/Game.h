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
	Tilemap* tilemap;

	float camX;
	float camY;
	float speed;
};

