#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include <Windows.h> // RECT

class Transform;

class RectCollider
{
public:
	RectCollider(DirectX::XMFLOAT2 size, Transform* transform);

	/// <summary>
	/// Gets bounds of the collider with already applied world position
	/// </summary>
	/// <returns> Bounds of the collider with already applied position </returns>
	RECT GetBounds();

	/// <summary>
	/// Gets bounds of the collider with already applied world position, but with an offset applied
	/// </summary>
	/// <param name="offset">: Offset for the collider in world position coordinates </param>
	/// <returns> Bounds of the collider with already applied position with an offset </returns>
	RECT GetBoundsWithOffset(DirectX::XMFLOAT2 offset);

private:
	// Is only updated when GetBounds() is called
	RECT bounds;
	DirectX::XMFLOAT2 size;

	// Transform of the gameobject
	Transform* transform;
};

