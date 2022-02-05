#pragma once

#include <d3d11.h> // DirectX classes

/// <summary>
/// Contains a pixel and vertex shader
/// </summary>
class Shader
{
public:
	Shader(const LPCWSTR vertexShaderFile, const LPCWSTR pixelShaderFile);
	~Shader();

	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	ID3D11InputLayout* GetInputLayout();

private:
	void CreateVertexShader(const LPCWSTR file, ID3D11Device* device);
	void CreatePixelShader(const LPCWSTR file, ID3D11Device* device);
	void CreateInputLayout(ID3D11Device* device, ID3DBlob* vsBuffer);

private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
};

