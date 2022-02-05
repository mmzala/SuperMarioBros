#include "Quad.h"
#include "../../SMBEngine.h" // Getting engine
#include "../DXManager.h" // Getting device

Quad::Quad(DirectX::XMFLOAT2 size)
	:
	vertexBuffer(nullptr)
{
	ID3D11Device* device = SMBEngine::GetInstance()->GetGraphics()->GetDevice();
	CreateVertexBuffer(device, size);
}

Quad::~Quad()
{
	if (vertexBuffer) vertexBuffer->Release();

	vertexBuffer = 0;
}

ID3D11Buffer** Quad::GetVertexBufferPP()
{
	return &vertexBuffer;
}

unsigned int Quad::GetSizeOfVertex()
{
	return sizeof(Vertex);
}

void Quad::CreateVertexBuffer(ID3D11Device* device, DirectX::XMFLOAT2 size)
{
	float halfWidth = (float)size.x / 2.0f;
	float halfHeight = (float)size.y / 2.0f;

	Vertex vertices[] =
	{
		{ DirectX::XMFLOAT3(halfWidth, halfHeight, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
		{ DirectX::XMFLOAT3(halfWidth, -halfHeight, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-halfWidth, -halfHeight, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

		{ DirectX::XMFLOAT3(-halfWidth, -halfHeight, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-halfWidth, halfHeight, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
		{ DirectX::XMFLOAT3(halfWidth, halfHeight, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(Vertex) * 6;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = vertices;

	HRESULT d3dResult = device->CreateBuffer(&vertexDesc,
		&resourceData, &vertexBuffer);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating vertex buffer!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
}
