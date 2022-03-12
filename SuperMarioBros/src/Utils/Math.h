#pragma once

class Math
{
public:
	static float Lerp(const float a, const float b, const float f)
	{
		return a + f * (b - a);
	}
};