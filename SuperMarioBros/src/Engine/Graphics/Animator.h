#pragma once

#include "Animation.h"

class Sprite;

class Animator
{
public:
	Animator(Sprite* sprite);
	~Animator();

	void Update(float deltaTime);

	/// <summary>
	/// Uses a custom animation speed instead of the one from the animation information
	/// </summary>
	/// <param name="deltaTime">: Delta timing </param>
	/// <param name="animationSpeed">: Speed of the animation </param>
	void Update(float deltaTime, float animationSpeed);
	void SetAnimation(Animation animation);

private:
	Sprite* sprite;
	Animation animation;

	float animationTimer;
};

