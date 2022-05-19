#pragma once

class Game;
class GameplayUI;
class AudioClip;

/// <summary>
/// Keeps track of the score, amount of coins and all other things needed for the UI
/// </summary>
class ScoreTracker
{
public:
	ScoreTracker(Game* game, float timeConversionSpeed);
	~ScoreTracker();

	void Update(const float deltaTime);

	/// <summary>
	/// Converts remaining time to score
	/// </summary>
	/// <param name="deltaTime">: DeltaTime </param>
	/// <returns>If conversion to score is complete (if time is 0)</returns>
	bool ConvertTimeToScore(const float deltaTime);
	void AddScore(int score);
	void AddScore(int score, float textPosX, float textPosY);
	void ResetScore();
	void AddCoin();
	void ResetCoins();
	void SetWorldText(const char* text);
	void SetTime(float time);
	float GetTime();

private:
	void UpdateScoreText();
	void UpdateCoinText();

public:
	bool stopTime;

private:
	Game* game;
	GameplayUI* gameplayUI;
	AudioClip* coinAddClip;

	int score;
	int coins;
	const char* world;
	float time;

	float timeConversionSpeed;
	float timeConversionTimer;
};

