#pragma once

#include <Windows.h> // HWND

class DXManager;
class Game;
class Camera;

class SMBEngine
{
public:
	SMBEngine();
	~SMBEngine();

	void Initialize(HWND hwnd);
	void Update();

	static SMBEngine* GetInstance();
	DXManager* GetGraphics();
	Camera* GetCamera();

private:
	static SMBEngine* engine;

	DXManager* graphics;
	Game* game;
	Camera* camera;
};

