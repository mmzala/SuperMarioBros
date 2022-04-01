#pragma once

#include "../../Engine/Graphics/UI/Canvas.h"

class Text;
class UISprite;

/// <summary>
/// Canvas already set up with all elements for gameplay UI
/// </summary>
class GameplayUI : private Canvas
{
public:
	GameplayUI();
	~GameplayUI() override;

	void Update() override;

public:
	Text* scoreText;
	Text* coinCountText;
	Text* worldCountText;
	Text* timeCountText;

private:
	Text* marioText;
	Text* worldText;
	Text* timeText;
	UISprite* coinSprite;
};

