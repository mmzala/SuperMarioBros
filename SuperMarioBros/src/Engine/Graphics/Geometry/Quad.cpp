#include "Quad.h"
#include "../../SMBEngine.h" // Getting engine
#include "../DXManager.h" // Getting device
#include <d3dcompiler.h> // D3DReadFileToBlob

Quad::Quad(DirectX::XMFLOAT2 size)
	:
	vertexShader(nullptr),
	pixelShader(nullptr),
	inputLayout(nullptr),
	vertexBuffer(nullptr)
{
	ID3D11Device* device = SMBEngine::GetInstance()->GetGraphics()->GetDevice();
	CreateVertexShader(device);
	CreatePixelShader(device);
	CreateVertexBuffer(device, size);
}

Quad::~Quad()
{
	if (vertexShader) vertexShader->Release();
	if (pixelShader) pixelShader->Release();
	if (inputLayout) inputLayout->Release();
	if (vertexBuffer) vertexBuffer->Release();

	vertexShader = 0;
	pixelShader = 0;
	inputLayout = 0;
	vertexBuffer = 0;
}

ID3D11VertexShader* Quad::GetVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* Quad::GetPixelShader()
{
	return pixelShader;
}

ID3D11InputLayout* Quad::GetInputLayout()
{
	return inputLayout;
}

ID3D11Buffer** Quad::GetVertexBufferPP()
{
	return &vertexBuffer;
}

unsigned int Quad::GetSizeOfVertex()
{
	return sizeof(Vertex);
}

void Quad::CreateVertexShader(ID3D11Device* device)
{
	ID3DBlob* vsBuffer = nullptr;
	HRESULT d3dResult = D3DReadFileToBlob(L"src/Engine/Graphics/Shaders/Precompiled/VertexShader.cso", &vsBuffer);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error loading vertex shader!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	d3dResult = device->CreateVertexShader(vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(), nullptr, &vertexShader);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating vertex shader!", L"Error!", MB_OK);
		if (vsBuffer) vsBuffer->Release();
		PostQuitMessage(0);
		return;
	}

	CreateInputLayout(device, vsBuffer);
	vsBuffer->Release();
}

void Quad::CreatePixelShader(ID3D11Device* device)
{
	ID3DBlob* psBuffer = nullptr;
	HRESULT d3dResult = D3DReadFileToBlob(L"src/Engine/Graphics/Shaders/Precompiled/PixelShader.cso", &psBuffer);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error loading pixel shader!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	d3dResult = device->CreatePixelShader(psBuffer->GetBufferPointer(),
		psBuffer->GetBufferSize(), nullptr, &pixelShader);
	psBuffer->Release();

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating pixel shader!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
}

void Quad::CreateInputLayout(ID3D11Device* device, ID3DBlob* vsBuffer)
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	unsigned int totalLayoutElements = ARRAYSIZE(inputDesc);

	HRESULT d3dResult = device->CreateInputLayout(inputDesc,
		totalLayoutElements, vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(),
		&inputLayout);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating input layout!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
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
