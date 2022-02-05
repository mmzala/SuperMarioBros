#include "Shader.h"
#include <d3dcompiler.h> // D3DReadFileToBlob
#include "../../SMBEngine.h" // Getting engine
#include "../DXManager.h" // Getting device

Shader::Shader(const LPCWSTR vertexShaderFile, const LPCWSTR pixelShaderFile)
	:
	vertexShader(nullptr),
	pixelShader(nullptr),
	inputLayout(nullptr)
{
	ID3D11Device* device = SMBEngine::GetInstance()->GetGraphics()->GetDevice();
	CreateVertexShader(vertexShaderFile, device);
	CreatePixelShader(pixelShaderFile, device);
}

Shader::~Shader()
{
	if (vertexShader) vertexShader->Release();
	if (pixelShader) pixelShader->Release();
	if (inputLayout) inputLayout->Release();

	vertexShader = 0;
	pixelShader = 0;
	inputLayout = 0;
}

ID3D11VertexShader* Shader::GetVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader* Shader::GetPixelShader()
{
	return pixelShader;
}

ID3D11InputLayout* Shader::GetInputLayout()
{
	return inputLayout;
}

void Shader::CreateVertexShader(const LPCWSTR file, ID3D11Device* device)
{
	ID3DBlob* vsBuffer = nullptr;
	HRESULT d3dResult = D3DReadFileToBlob(file, &vsBuffer);

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

void Shader::CreatePixelShader(const LPCWSTR file, ID3D11Device* device)
{
	ID3DBlob* psBuffer = nullptr;
	HRESULT d3dResult = D3DReadFileToBlob(file, &psBuffer);

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

void Shader::CreateInputLayout(ID3D11Device* device, ID3DBlob* vsBuffer)
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