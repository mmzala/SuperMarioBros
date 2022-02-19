#pragma once

class GameObject;
class Mario;
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
	Mario* player;
	Tilemap* tilemap;

	float camX;
	float camY;
	float speed;
};

