#include "Texture2D.h"
#include "../SMBEngine.h" // Getting engine
#include "DXManager.h" // Gettings device
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // stbi_load / image data loader

Texture2D::Texture2D(const char* file)
	:
	width(0),
	height(0),
	texture(nullptr),
	colorMap(nullptr),
	colorMapSampler(nullptr)
{
	ID3D11Device* device = SMBEngine::GetInstance()->GetGraphics()->GetDevice();
	CreateTexture(file, device);
	CreateShaderResourceView(device);
	CreateSamplerState(device);
}

Texture2D::~Texture2D()
{
	if (colorMapSampler) colorMapSampler->Release();
	if (colorMap) colorMap->Release();
	if (texture) texture->Release();

	colorMapSampler = 0;
	colorMap = 0;
	texture = 0;
}

ID3D11ShaderResourceView** Texture2D::GetShaderResourceViewPP()
{
	return &colorMap;
}

ID3D11SamplerState** Texture2D::GetSamplerStatePP()
{
	return &colorMapSampler;
}

int Texture2D::GetWidth()
{
	return width;
}

int Texture2D::GetHeight()
{
	return height;
}

void Texture2D::CreateTexture(const char* file, ID3D11Device* device)
{
	int imgChannels;
	const int imgDesiredChannels = 4;

	stbi_uc* imgData = stbi_load(file, &width, &height, &imgChannels, imgDesiredChannels);
	int imgPitch = width * 4;

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
	textureSubresourceData.pSysMem = imgData;
	textureSubresourceData.SysMemPitch = imgPitch;

	HRESULT d3dResult = device->CreateTexture2D(&textureDesc, &textureSubresourceData, &texture);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating texture 2D!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	stbi_image_free(imgData);
}

void Texture2D::CreateShaderResourceView(ID3D11Device* device)
{
	HRESULT d3dResult = device->CreateShaderResourceView(texture, nullptr, &colorMap);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating shader resource view!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
}

void Texture2D::CreateSamplerState(ID3D11Device* device)
{
	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT d3dResult = device->CreateSamplerState(&colorMapDesc, &colorMapSampler);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating sampler state!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
}
