#pragma once

#include <Windows.h> // HWND

class DXManager;
class Game;
class Camera;
class Input;
class Timer;
class Shader;

class SMBEngine
{
public:
	SMBEngine(HWND hwnd);
	~SMBEngine();

	void Update();

	static SMBEngine* GetInstance();
	DXManager* GetGraphics();
	Camera* GetCamera();

	Shader* GetSpriteShader();

private:
	void Initialize(HWND hwnd);

private:
	static SMBEngine* instance;

	DXManager* graphics;
	Camera* camera;
	Game* game;
	Input* input;
	Timer* timer;

	Shader* spriteShader;
};

