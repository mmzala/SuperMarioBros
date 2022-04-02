#include "RectBounds.h"
#include "../../Game/GameObjects/Components/Transform.h"

RectBounds::RectBounds(DirectX::XMFLOAT2 size, Transform* transform)
	:
	bounds(Rect()),
	colliderSize(size),
	sizeOffset(DirectX::XMFLOAT2()),
	transform(transform)
{}

RectBounds::~RectBounds()
{}

Rect RectBounds::GetBounds()
{
	// Update bounds
	float halfWidth = colliderSize.x / 2.0f;
	float halfHeight = colliderSize.y / 2.0f;
	
	// Left and bottom are the position values, so only apply them there
	bounds.x = transform->position.x - halfWidth * transform->scale.x;
	bounds.width = (colliderSize.x * transform->scale.x) + sizeOffset.x;
	bounds.y = transform->position.y - halfHeight * transform->scale.y;
	bounds.height = (colliderSize.y * transform->scale.y) + sizeOffset.y;

	return bounds;
}

Rect RectBounds::GetBoundsWithOffset(DirectX::XMFLOAT2 positionOffset)
{
	Rect bounds = GetBounds();

	// Left and bottom are the position values, so only apply them there
	bounds.x += positionOffset.x;
	bounds.y += positionOffset.y;

	return bounds;
}

void RectBounds::SetSizeOffset(DirectX::XMFLOAT2 offset)
{
	sizeOffset = offset;
}
