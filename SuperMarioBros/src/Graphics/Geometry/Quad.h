#pragma once

#include <d3d11.h> // DirectX classes
#include <DirectXMath.h>

/// <summary>
/// A flat surface to draw a texture on
/// </summary>
class Quad
{
public:
	Quad(ID3D11Device* device);
	~Quad();

	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	ID3D11InputLayout* GetInputLayout();
	ID3D11Buffer** GetVertexBufferPP();

	/// <summary>
	/// Uses sizeof() to get the size of the Vertex struct used for vertecies
	/// </summary>
	/// <returns> Size of Vertex struct </returns>
	unsigned int GetSizeOfVertex();

private:
	void CreateVertexShader(ID3D11Device* device);
	void CreatePixelShader(ID3D11Device* device);
	void CreateInputLayout(ID3D11Device* device, ID3DBlob* vsBuffer);
	void CreateVertexBuffer(ID3D11Device* device);

private:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex0;
	};

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vertexBuffer;
};

