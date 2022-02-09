#pragma once

#include <DirectXMath.h> // XMMATRIX and XMFLOAT2

class Transform
{
public:
	Transform();

	DirectX::XMMATRIX GetWorldMatrix();

public:
	DirectX::XMFLOAT2 position;
	float rotation;
	DirectX::XMFLOAT2 scale;
};

