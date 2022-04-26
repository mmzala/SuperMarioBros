#pragma once

class GameplayUI;

/// <summary>
/// Keeps track of the score, amount of coins and all other things needed for the UI
/// </summary>
class ScoreTracker
{
public:
	ScoreTracker(float timeConversionSpeed);
	~ScoreTracker();

	void Update(const float deltaTime);

	bool ConvertTimeToScore(const float deltaTime);
	void AddScore(int score);
	void ResetScore();
	void AddCoin();
	void ResetCoins();
	void SetWorldText(const char* text);
	void SetTime(float time);

private:
	void UpdateScoreText();
	void UpdateCoinText();

public:
	bool stopTime;

private:
	GameplayUI* gameplayUI;

	int score;
	int coins;
	const char* world;
	float time;

	float timeConversionSpeed;
	float timeConversionTimer;
};

