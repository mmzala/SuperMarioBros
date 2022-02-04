#pragma once

#include <DirectXMath.h> // XMMATRIX and XMFLOAT2

class Sprite;

class GameObject
{
public:
	GameObject(const char* textureFile);
	~GameObject();

	void Update(float deltaTime);

	DirectX::XMMATRIX GetWorldMatrix();
	void SetPosition(DirectX::XMFLOAT2 position);
	void SetRotation(float rotation);
	void SetScale(DirectX::XMFLOAT2 scale);

private:
	DirectX::XMFLOAT2 position;
	float rotation;
	DirectX::XMFLOAT2 scale;

	Sprite* sprite;
};

