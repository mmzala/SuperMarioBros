#pragma once

#include <d3d11.h> // DirectX classes

class Texture2D
{
public:
	Texture2D(const char* file, ID3D11Device* device);
	~Texture2D();

	ID3D11ShaderResourceView** GetShaderResourceViewPP();
	ID3D11SamplerState** GetSamplerStatePP();

private:
	void CreateTexture(const char* file, ID3D11Device* device);
	void CreateShaderResourceView(ID3D11Device* device);
	void CreateSamplerState(ID3D11Device* device);

private:
	int width;
	int height;

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* colorMap;
	ID3D11SamplerState* colorMapSampler;
};

