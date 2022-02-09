#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include <Windows.h> // RECT

class Transform;

class RectCollider
{
public:
	RectCollider(DirectX::XMFLOAT2 size, Transform* transform);

	RECT GetBounds();

private:
	// Is only updated when GetBounds() is called
	RECT bounds;
	DirectX::XMFLOAT2 size;

	// Transform of the gameobject
	Transform* transform;
};

