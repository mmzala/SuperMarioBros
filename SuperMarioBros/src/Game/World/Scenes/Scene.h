#pragma once

class Game;

class Scene
{
public:
	Scene(Game* game);
	virtual ~Scene();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(const float deltaTime);

protected:
	/// <summary>
	/// Each scene in SMB has the main UI that shows the score, time etc.
	/// </summary>
	virtual void CreateUI();
	void SetupScoreTracker(const char* worldText, float time, bool stopTime);

protected:
	Game* game;
};

