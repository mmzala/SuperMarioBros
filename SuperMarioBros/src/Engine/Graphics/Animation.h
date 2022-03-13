#pragma once

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

	bool operator==(const Animation& other)
	{
		if (startFrame == other.startFrame &&
			endFrame == other.endFrame &&
			speed == other.speed)
		{
			return true;
		}

		return false;
	}
};