#pragma once

class DXManager;
class Sprite;

/// <summary>
/// Manages the game itself
/// </summary>
class Game
{
public:
	Game(DXManager* DXManage);
	~Game();

	void Update(float deltaTime);

private:
	DXManager* graphics;
	Sprite* sprite;
};

