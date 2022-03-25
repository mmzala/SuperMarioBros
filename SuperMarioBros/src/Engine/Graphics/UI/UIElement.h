#pragma once

#include <DirectXMath.h>

class Transform;

class UIElement
{
public:
	UIElement();
	virtual ~UIElement();

	virtual void Draw(DirectX::XMFLOAT2 anchor);

public:
	Transform* transform;
};

