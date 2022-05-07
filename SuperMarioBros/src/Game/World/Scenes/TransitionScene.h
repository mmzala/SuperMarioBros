#pragma once

#include "Scene.h"

class DXManager;
class GameObject;
class Canvas;

class TransitionScene : public Scene
{
public:
	TransitionScene(Game* game);
	~TransitionScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

	void SetSceneToTransitionTo(int sceneIndex);

protected:
	void CreateUI() override;

private:
	DXManager* graphics;

	GameObject* mario;
	Canvas* canvas;

	const char* transitionToWorld;
	int transitionToScene;
	float timeToTransition;
};

