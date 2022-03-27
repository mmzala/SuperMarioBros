#include "Camera.h"
#include <algorithm> // std::clamp

Camera::Camera(const unsigned int clientWidth, const unsigned int clientHeight)
	:
	clientWidth((float)clientWidth),
	clientHeight((float)clientHeight),
	position(DirectX::XMFLOAT2(0.0f, 0.0f)),
	viewportProjectionMatrix(DirectX::XMMATRIX()),
	boundary(Rect())
{
	UpdateViewportProjectionMatrix();
}

Camera::~Camera()
{}

void Camera::SetPosition(DirectX::XMFLOAT2 position)
{
	// If boundary is the same as default Rect, then that means there are no boundaries
	if (boundary != Rect())
	{
		position.x = std::clamp(position.x, boundary.x, boundary.width);
		position.y = std::clamp(position.y, boundary.y, boundary.height);
	}

	this->position = position;
	UpdateViewportProjectionMatrix();
}

DirectX::XMMATRIX Camera::GetViewportProjectionMatrix()
{
	return viewportProjectionMatrix;
}

Rect Camera::GetViewportBounds()
{
	Rect bounds = Rect();
	bounds.x = position.x;
	bounds.width = clientWidth + position.x;
	bounds.y = position.y;
	bounds.height = clientHeight + position.y;

	return bounds;
}

DirectX::XMFLOAT2 Camera::GetViewportCenter()
{
	DirectX::XMFLOAT2 center = DirectX::XMFLOAT2();

	center.x = position.x + clientWidth / 2;
	center.y = position.y + clientHeight / 2;

	return center;
}

void Camera::FollowPosition(DirectX::XMFLOAT2 position, bool followX, bool followY)
{
	Rect viewportBounds = GetViewportBounds();
	DirectX::XMFLOAT2 finalPosition = this->position;

	if (followX) finalPosition.x = position.x - clientWidth / 2;
	if (followY) finalPosition.y = position.y - clientHeight / 2;

	SetPosition(finalPosition);
}

void Camera::SetBoundary(Rect boundary)
{
	// If boundary is too small for the viewport, then return
	if (boundary.x + boundary.width < clientWidth ||
		boundary.y + boundary.height < clientHeight) return;

	boundary.width -= clientWidth;
	boundary.height -= clientHeight;
	this->boundary = boundary;

	SetPosition(position);
}

void Camera::ResetBoundary()
{
	boundary = Rect();
}

void Camera::UpdateViewportProjectionMatrix()
{
	using namespace DirectX;

	XMMATRIX view = XMMatrixIdentity();
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f + position.x, clientWidth + position.x,
		0.0f + position.y, clientHeight + position.y, 0.1f, 100.0f);

	viewportProjectionMatrix = XMMatrixMultiply(view, projection);
}
