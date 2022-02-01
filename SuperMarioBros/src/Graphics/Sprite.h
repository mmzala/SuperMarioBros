#pragma once

class Quad;
class Texture2D;
struct ID3D11Device;
struct ID3D11DeviceContext;

class Sprite
{
public:
	Sprite(const char* textureFile, ID3D11Device* device);
	~Sprite();

	void Draw(ID3D11DeviceContext* deviceContext);

private:
	Quad* quad;
	Texture2D* texture;
};

