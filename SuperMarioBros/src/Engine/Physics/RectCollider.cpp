#include "RectCollider.h"
#include "../../Game/GameObjects/Components/Transform.h"

RectCollider::RectCollider(DirectX::XMFLOAT2 size, Transform* transform)
	:
	bounds(Rect()),
	colliderSize(size),
	sizeOffset(DirectX::XMFLOAT2()),
	transform(transform)
{}

RectCollider::~RectCollider()
{}

Rect RectCollider::GetBounds()
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

Rect RectCollider::GetBoundsWithOffset(DirectX::XMFLOAT2 positionOffset)
{
	Rect bounds = GetBounds();

	// Left and bottom are the position values, so only apply them there
	bounds.x += positionOffset.x;
	bounds.y += positionOffset.y;

	return bounds;
}

void RectCollider::SetSizeOffset(DirectX::XMFLOAT2 offset)
{
	sizeOffset = offset;
}
