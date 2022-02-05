#include "Camera.h"

Camera::Camera(const unsigned int clientWidth, const unsigned int clientHeight)
	:
	clientWidth((float)clientWidth),
	clientHeight((float)clientHeight),
	position(DirectX::XMFLOAT2(-200.0f, -200.0f)),
	viewportProjectionMatrix(DirectX::XMMATRIX())
{
	UpdateViewportProjectionMatrix();
}

Camera::~Camera()
{}

void Camera::SetPosition(DirectX::XMFLOAT2 position)
{
	this->position = position;
	UpdateViewportProjectionMatrix();
}

DirectX::XMMATRIX Camera::GetViewportProjectionMatrix()
{
	return viewportProjectionMatrix;
}

void Camera::UpdateViewportProjectionMatrix()
{
	using namespace DirectX;

	XMMATRIX view = XMMatrixIdentity();
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f + position.x, clientWidth + position.x,
		0.0f + position.y, clientHeight + position.y, 0.1f, 100.0f);

	viewportProjectionMatrix = XMMatrixMultiply(view, projection);
}
