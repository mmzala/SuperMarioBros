#include "RectCollider.h"
#include "../../Game/GameObjects/Components/Transform.h"

RectCollider::RectCollider(DirectX::XMFLOAT2 size, Transform* transform)
	:
	bounds(Rect()),
	size(size),
	transform(transform)
{}

Rect RectCollider::GetBounds()
{
	// Update bounds
	float halfWidth = size.x / 2.0f;
	float halfHeight = size.y / 2.0f;
	
	// Left and bottom are the position values, so only apply them there
	bounds.x = transform->position.x - halfWidth * transform->scale.x;
	bounds.width = size.x * transform->scale.x;
	bounds.y = transform->position.y - halfHeight * transform->scale.y;
	bounds.height = size.y * transform->scale.y;

	return bounds;
}

Rect RectCollider::GetBoundsWithOffset(DirectX::XMFLOAT2 offset)
{
	Rect bounds = GetBounds();

	// Left and bottom are the position values, so only apply them there
	bounds.x += offset.x;
	bounds.y += offset.y;

	return bounds;
}
