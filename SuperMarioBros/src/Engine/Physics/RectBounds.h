#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include "../../Utils/Rect.h"

class Transform;

class RectBounds
{
public:
	RectBounds(DirectX::XMFLOAT2 size, Transform* transform);
	~RectBounds();

	/// <summary>
	/// Gets bounds of the collider with already applied world position
	/// </summary>
	/// <returns> Bounds of the collider with already applied position </returns>
	Rect GetBounds();

	/// <summary>
	/// Gets bounds of the collider with already applied world position, but with an offset applied
	/// </summary>
	/// <param name="positionOffset">: Offset for the collider position </param>
	/// <returns> Bounds of the collider with already applied position with an offset </returns>
	Rect GetBoundsWithOffset(DirectX::XMFLOAT2 positionOffset);

	void SetSizeOffset(DirectX::XMFLOAT2 offset);

private:
	// Is only updated when GetBounds() is called
	Rect bounds;
	DirectX::XMFLOAT2 colliderSize;
	DirectX::XMFLOAT2 sizeOffset;

	// Transform of the gameobject
	Transform* transform;
};

