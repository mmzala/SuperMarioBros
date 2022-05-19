#include "ScoreTracker.h"
#include "../Game.h"
#include "../UI/GameplayUI.h"
#include "../../Engine/Graphics/UI/Text.h"
#include "../Data/ScoreData.h" // Scoring data for converting time to score
#include "../../Engine/Audio/AudioClip.h" // Audio
#include <iomanip> // std::setprecision
#include <sstream> // std::stringstream
#include "../World/Scenes/GameplayScene.h" // Spawning scoring text

ScoreTracker::ScoreTracker(Game* game, float timeConversionSpeed)
	:
	stopTime(true),
	game(game),
	gameplayUI(new GameplayUI()),
	coinAddClip(new AudioClip("assets/CoinPickUp.wav", false)),
	score(0),
	coins(0),
	world(""),
	time(0.0f),
	timeConversionSpeed(timeConversionSpeed),
	timeConversionTimer(0.0f)
{}

ScoreTracker::~ScoreTracker()
{
	delete gameplayUI;
	delete coinAddClip;
}

void ScoreTracker::Update(const float deltaTime)
{
	if (!stopTime && time > 0.0f)
	{
		SetTime(time);
		time -= deltaTime;
	}

	gameplayUI->Update();
}

void ScoreTracker::ResetScore()
{
	score = 0;
	UpdateScoreText();
}

bool ScoreTracker::ConvertTimeToScore(const float deltaTime)
{
	if (time <= 0.0f)
	{
		SetTime(0.0f); // In the last loop the middle character becomes '-', I don't really feel like fixing it, so here is the fix :D
		return true;
	}

	stopTime = true;

	timeConversionTimer += timeConversionSpeed * deltaTime;
	if (timeConversionTimer > 1.0f)
	{
		SetTime(time - 1.0f);
		AddScore(ScoreData::SecondToScore);
		timeConversionTimer = 0.0f;
	}

	return false;
}

void ScoreTracker::AddScore(int score)
{
	this->score += score;
	UpdateScoreText();
}

void ScoreTracker::AddScore(int score, float textPosX, float textPosY)
{
	GameplayScene* scene = static_cast<GameplayScene*>(game->GetCurrentScene());
	if (scene)
	{
		std::string scoreString = std::to_string(score);
		scene->SpawnScoringText({ textPosX, textPosY }, scoreString.c_str());
	}

	AddScore(score);
}

void ScoreTracker::AddCoin()
{
	coins++;
	coinAddClip->Play();
	UpdateCoinText();
}

void ScoreTracker::ResetCoins()
{
	coins = 0;
	UpdateCoinText();
}

void ScoreTracker::SetWorldText(const char* text)
{
	gameplayUI->worldCountText->SetText(text);
}

void ScoreTracker::SetTime(float time)
{
	this->time = time;

	// Display time without decimals
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << time;
	std::string timeString = stream.str();

	// Time always has 3 numbers
	timeString = std::string(3 - (int)std::fmin(3, static_cast<int>(timeString.length())), '0') + timeString;
	const char* timeText = timeString.c_str();
	gameplayUI->timeCountText->SetText(timeText);
}

float ScoreTracker::GetTime()
{
	return time;
}

void ScoreTracker::UpdateScoreText()
{
	// Score always has 6 numbers
	std::string scoreString = std::to_string(score);
	scoreString = std::string(6 - (int)std::fmin(6, static_cast<int>(scoreString.length())), '0') + scoreString;
	gameplayUI->scoreText->SetText(scoreString.c_str());
}

void ScoreTracker::UpdateCoinText()
{
	// Coins always has 2 numbers
	std::string coinsString = std::to_string(coins);
	coinsString = std::string(2 - (int)std::fmin(2, static_cast<int>(coinsString.length())), '0') + coinsString;
	coinsString = "x" + coinsString;
	gameplayUI->coinCountText->SetText(coinsString.c_str());
}
