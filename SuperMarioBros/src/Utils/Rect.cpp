#include "Rect.h"

Rect::Rect(float x, float y, float width, float height)
	:
	x(x),
	y(y),
	width(width),
	height(height)
{}

Rect::~Rect()
{}

bool Rect::operator!=(const Rect & other)
{
	if (x == other.x && width == other.width &&
		y == other.y && height == other.height) return false;

	return true;
}
