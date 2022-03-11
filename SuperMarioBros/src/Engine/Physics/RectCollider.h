#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include "../../Utils/Rect.h"

class Transform;

class RectCollider
{
public:
	RectCollider(DirectX::XMFLOAT2 size, Transform* transform);

	/// <summary>
	/// Gets bounds of the collider with already applied world position
	/// </summary>
	/// <returns> Bounds of the collider with already applied position </returns>
	Rect GetBounds();

	/// <summary>
	/// Gets bounds of the collider with already applied world position, but with an offset applied
	/// </summary>
	/// <param name="offset">: Offset for the collider in world position coordinates </param>
	/// <returns> Bounds of the collider with already applied position with an offset </returns>
	Rect GetBoundsWithOffset(DirectX::XMFLOAT2 offset);

private:
	// Is only updated when GetBounds() is called
	Rect bounds;
	DirectX::XMFLOAT2 size;

	// Transform of the gameobject
	Transform* transform;
};

