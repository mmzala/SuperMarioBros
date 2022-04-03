#include "ScoreTracker.h"
#include "../UI/GameplayUI.h"
#include "../../Engine/Graphics/UI/Text.h"
#include <iomanip> // std::setprecision
#include <sstream> // std::stringstream

ScoreTracker::ScoreTracker()
	:
	stopTime(true),
	gameplayUI(new GameplayUI()),
	score(0),
	coins(0),
	world(""),
	time(0.0f)
{}

ScoreTracker::~ScoreTracker()
{
	delete gameplayUI;
}

void ScoreTracker::Update(const float deltaTime)
{
	if (!stopTime && time > 0.0f)
	{
		time -= deltaTime;
		SetTime(time);
	}

	gameplayUI->Update();
}

void ScoreTracker::AddScore(int score)
{
	this->score += score;
	std::string scoreString = std::to_string(score);

	// Score always has 6 numbers
	scoreString = std::string(6 - std::min(6, static_cast<int>(scoreString.length())), '0') + scoreString;
	gameplayUI->scoreText->SetText(scoreString.c_str());
}

void ScoreTracker::AddCoin()
{
	coins++;
	std::string coinsString = std::to_string(coins);

	// Coins always has 2 numbers
	coinsString = std::string(2 - std::min(2, static_cast<int>(coinsString.length())), '0') + coinsString;
	coinsString = "x" + coinsString;
	gameplayUI->coinCountText->SetText(coinsString.c_str());
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
	timeString = std::string(3 - std::min(3, static_cast<int>(timeString.length())), '0') + timeString;
	const char* timeText = timeString.c_str();
	gameplayUI->timeCountText->SetText(timeText);
}
