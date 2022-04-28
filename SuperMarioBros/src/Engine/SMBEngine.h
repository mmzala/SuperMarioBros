#pragma once

#include <Windows.h> // HWND

class DXManager;
class AudioManager;
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
	AudioManager* GetAudioManager();
	Camera* GetCamera();
	Game* GetGame();

	Shader* GetSpriteShader();

	/// <summary>
	/// This method is ment for classes that don't have direct access to deltaTime
	/// </summary>
	/// <returns> Delta time </returns>
	float GetDeltaTime();

private:
	void Initialize(HWND hwnd);

private:
	static SMBEngine* instance;
	float deltaTime;

	DXManager* graphics;
	Camera* camera;
	Input* input;
	AudioManager* audioManager;
	Timer* timer;
	Game* game;

	Shader* spriteShader;
};

