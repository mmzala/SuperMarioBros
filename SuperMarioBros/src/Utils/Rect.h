#pragma once

class Rect
{
public:
	Rect(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f);
	~Rect();

	bool operator!=(const Rect& other);

public:
	float x;
	float y;
	float width;
	float height;
};

