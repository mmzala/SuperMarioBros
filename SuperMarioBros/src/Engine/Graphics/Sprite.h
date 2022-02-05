#pragma once

#include <DirectXMath.h> // XMMATRIX

class Texture2D;
class Quad;
struct ID3D11Buffer;

class Sprite
{
public:
	Sprite(const char* textureFile);
	~Sprite();

	void Draw(DirectX::XMMATRIX worldMatrix);

private:
	void CreateConstantBuffer();

private:
	ID3D11Buffer* constantBuffer;

	Texture2D* texture;
	Quad* quad;
};

