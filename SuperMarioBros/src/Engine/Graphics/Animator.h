#pragma once

class Sprite;

struct Animation
{
	int startFrame;
	int endFrame;
	// Animation frames per second
	float speed;

	Animation(int startFrame, int endFrame, float speed)
		:
		startFrame(startFrame),
		endFrame(endFrame),
		speed(speed)
	{}
};

class Animator
{
public:
	Animator(Sprite* sprite);
	~Animator();

	void Update(float deltaTime);
	void SetAnimation(Animation animation);

private:
	Sprite* sprite;
	Animation animation;

	float animationTimer;
};

