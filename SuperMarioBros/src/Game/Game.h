#pragma once

class GameObject;
class Mario;
class Goomba;
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
	Mario* player;
	Goomba* goomba;
};

