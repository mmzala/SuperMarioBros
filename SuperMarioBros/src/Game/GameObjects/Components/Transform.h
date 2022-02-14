#pragma once

#include <DirectXMath.h> // XMMATRIX and XMFLOAT2

class Transform
{
public:
	Transform(DirectX::XMFLOAT2 position = { 0.0f, 0.0f },
		float rotation = 0.0f, DirectX::XMFLOAT2 scale = { 1.0f, 1.0f });

	DirectX::XMMATRIX GetWorldMatrix();

public:
	DirectX::XMFLOAT2 position;
	float rotation;
	DirectX::XMFLOAT2 scale;
};

