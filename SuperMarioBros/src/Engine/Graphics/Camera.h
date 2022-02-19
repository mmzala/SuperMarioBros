#pragma once

#include <DirectXMath.h> // XMMATRIX
#include <Windows.h> // RECT

class Camera
{
public:
	Camera(const unsigned int clientWidth, const unsigned int clientHeight);
	~Camera();

	void SetPosition(DirectX::XMFLOAT2 position);
	DirectX::XMMATRIX GetViewportProjectionMatrix();

	RECT GetViewportBounds();

private:
	void UpdateViewportProjectionMatrix();

private:
	const float clientWidth;
	const float clientHeight;

	DirectX::XMFLOAT2 position;
	DirectX::XMMATRIX viewportProjectionMatrix;
};

