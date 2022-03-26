#pragma once

class Canvas;
class Text;
class UISprite;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(const float deltaTime);

protected:
	/// <summary>
	/// Each scene in SMB has the main UI that shows the score, time etc.
	/// </summary>
	virtual void CreateUI();

protected:
	Canvas* gameCanvas;
	Text* marioText;
	Text* scoreText;
	Text* coinCountText;
	Text* worldText;
	Text* worldCountText;
	Text* timeText;
	Text* timeCountText;
	UISprite* coinSprite;
};

