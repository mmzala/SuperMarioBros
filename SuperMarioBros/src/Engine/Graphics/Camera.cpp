#include "Camera.h"

Camera::Camera(const unsigned int clientWidth, const unsigned int clientHeight)
	:
	viewportProjectionMatrix(DirectX::XMMATRIX())
{
	using namespace DirectX;
	XMMATRIX view = XMMatrixIdentity();
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f, (float)clientWidth, 0.0f, (float)clientHeight, 0.1f, 100.0f);
	viewportProjectionMatrix = XMMatrixMultiply(view, projection);
}

Camera::~Camera()
{}

DirectX::XMMATRIX Camera::GetViewportProjectionMatrix()
{
	return viewportProjectionMatrix;
}
