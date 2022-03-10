#pragma once

#include <DirectXMath.h> // XMMATRIX
#include "../Physics/Rect.h"

class Camera
{
public:
	Camera(const unsigned int clientWidth, const unsigned int clientHeight);
	~Camera();

	void SetPosition(DirectX::XMFLOAT2 position);
	DirectX::XMMATRIX GetViewportProjectionMatrix();
	Rect GetViewportBounds();
	DirectX::XMFLOAT2 GetViewportCenter();

	/// <summary>
	/// Follows the position on the given axis. The center of the viewport is the given position
	/// </summary>
	/// <param name="position">: Position to follow</param>
	/// <param name="followX">: If camera should follow on X axis</param>
	/// <param name="followY">: If camera should follow on Y axis</param>
	void FollowPosition(DirectX::XMFLOAT2 position, bool followX, bool followY);

	/// <summary>
	/// Sets the boundery for the camera. The camera connot go outside those boundaries
	/// </summary>
	/// <param name="boundary">: boundary for the camera</param>
	void SetBoundary(Rect boundary);

private:
	void UpdateViewportProjectionMatrix();

private:
	const float clientWidth;
	const float clientHeight;

	DirectX::XMFLOAT2 position;
	DirectX::XMMATRIX viewportProjectionMatrix;

	Rect boundary;
};

