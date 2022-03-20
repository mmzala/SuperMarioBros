#pragma once

class GameObject;
class Mario;
class Goomba;
class Tilemap;
class Flag;
struct TilemapAnimation;

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
	Flag* flag;

	TilemapAnimation* questionMarkBlock;
};

