#pragma once

#include <d3d11.h> // DirectX classes
#include <DirectXMath.h> // XMFLOAT2

/// <summary>
/// A flat surface to draw a texture on
/// </summary>
class Quad
{
public:
	Quad(DirectX::XMFLOAT2 size);
	~Quad();

	ID3D11Buffer** GetVertexBufferPP();

	/// <summary>
	/// Uses sizeof() to get the size of the Vertex struct used for vertecies
	/// </summary>
	/// <returns> Size of Vertex struct </returns>
	unsigned int GetSizeOfVertex();

private:
	void CreateVertexBuffer(ID3D11Device* device, DirectX::XMFLOAT2 size);

private:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex0;
	};

	ID3D11Buffer* vertexBuffer;
};

