#include "Transform.h"

Transform::Transform(DirectX::XMFLOAT2 position,
	float rotation, DirectX::XMFLOAT2 scale)
	:
	position(position),
	rotation(rotation),
	scale(scale)
{}

DirectX::XMMATRIX Transform::GetWorldMatrix()
{
	using namespace DirectX;

	XMMATRIX translation = XMMatrixTranslation(position.x, position.y, 0.0f);
	XMMATRIX rotation = XMMatrixRotationZ(this->rotation);
	XMMATRIX scale = XMMatrixScaling(this->scale.x, this->scale.y, 1.0f);

	return scale * rotation * translation;
}
