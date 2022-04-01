#include "Scene.h"

#include "../../GameObjects/Components/Transform.h"

// Camera resetting
#include "../../../Engine/SMBEngine.h"
#include "../../../Engine/Graphics/Camera.h"

Scene::Scene()
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
