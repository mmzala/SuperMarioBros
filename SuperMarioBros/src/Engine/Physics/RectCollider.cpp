#include "RectCollider.h"
#include "../../Game/GameObjects/Components/Transform.h"

RectCollider::RectCollider(DirectX::XMFLOAT2 size, Transform* transform)
	:
	bounds(RECT()),
	size(size),
	transform(transform)
{}

RECT RectCollider::GetBounds()
{
	// Update bounds
	float halfWidth = size.x / 2.0f;
	float halfHeight = size.y / 2.0f;
	
	bounds.left = (LONG)(transform->position.x - halfWidth * transform->scale.x);
	bounds.right = (LONG)(size.x * transform->scale.x);
	bounds.bottom = (LONG)(transform->position.y - halfHeight * transform->scale.y);
	bounds.top = (LONG)(size.y * transform->scale.y);

	return bounds;
}
