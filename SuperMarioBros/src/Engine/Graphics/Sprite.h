#pragma once

#include <DirectXMath.h> // XMMATRIX

class Texture2D;
class Quad;
class DXManager;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
struct ID3D11BlendState;

class Sprite
{
public:
	Sprite(const char* textureFile);
	~Sprite();

	void Draw(DirectX::XMMATRIX worldMatrix);

private:
	void CreateConstantBuffer(ID3D11Device* device);
	void CreateBlendState(DXManager* graphics);

private:
	ID3D11Buffer* constantBuffer;
	ID3D11BlendState* alphaBlendState;

	Texture2D* texture;
	Quad* quad;
};

