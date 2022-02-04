#pragma once

#include <DirectXMath.h> // XMMATRIX

class Camera
{
public:
	Camera(const unsigned int clientWidth, const unsigned int clientHeight);
	~Camera();

	DirectX::XMMATRIX GetViewportProjectionMatrix();

private:
	DirectX::XMMATRIX viewportProjectionMatrix;
};

