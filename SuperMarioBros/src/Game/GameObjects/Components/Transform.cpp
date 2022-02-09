#include "Transform.h"

Transform::Transform()
	:
	position(DirectX::XMFLOAT2(0.0f, 0.0f)),
	rotation(0.0f),
	scale(DirectX::XMFLOAT2(1.0f, 1.0f))
{}

DirectX::XMMATRIX Transform::GetWorldMatrix()
{
	using namespace DirectX;

	XMMATRIX translation = XMMatrixTranslation(position.x, position.y, 0.0f);
	XMMATRIX rotation = XMMatrixRotationZ(this->rotation);
	XMMATRIX scale = XMMatrixScaling(this->scale.x, this->scale.y, 1.0f);

	return scale * rotation * translation;
}
