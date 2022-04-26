#include "Scene.h"
#include "../../Game.h"
#include "../../GameObjects/Components/Transform.h"

// Camera resetting
#include "../../../Engine/SMBEngine.h"
#include "../../../Engine/Graphics/Camera.h"

// Setting scoring UI
#include "../../Scoring/ScoreTracker.h"

Scene::Scene(Game* game)
	:
	game(game)
{}

Scene::~Scene()
{}

void Scene::Load()
{
	Camera* camera = SMBEngine::GetInstance()->GetCamera();
	camera->ResetBoundary();
	camera->SetPosition(DirectX::XMFLOAT2(0.0f, 0.0f));
	CreateUI();
}

void Scene::UnLoad()
{}

void Scene::Update(const float deltaTime)
{}

void Scene::CreateUI()
{}

void Scene::SetupScoreTracker(const char* worldText, float time, bool stopTime, bool resetScore, bool resetCoins)
{
	ScoreTracker* scoreTracker = game->GetScoreTracker();
	scoreTracker->SetWorldText(worldText);
	scoreTracker->SetTime(time);
	scoreTracker->stopTime = stopTime;
	if (resetScore) scoreTracker->ResetScore();
	if (resetCoins) scoreTracker->ResetCoins();
}
