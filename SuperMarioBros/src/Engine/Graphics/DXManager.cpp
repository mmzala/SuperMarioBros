#include "DXManager.h"
#include <d3dcompiler.h> // D3DCOMPILE Constants

// Prefer 'enum class' over 'enum' warning (thanks Microsoft >_<)
#pragma warning(disable : 26812)

DXManager::DXManager(HWND hwnd, const unsigned int clientWidth, const unsigned int clientHeight)
	:
	device(nullptr),
	deviceContext(nullptr),
	swapChain(nullptr),
	backBufferTarget(nullptr),
	constantBuffer(),
	alphaBlendState(nullptr),
	driverType(D3D_DRIVER_TYPE_NULL),
	featureLevel(D3D_FEATURE_LEVEL_11_0)
{
	if (!CreateDeviceAndSwapChain(hwnd, clientWidth, clientHeight)) return;
	if(!CreateRenderTargetView()) return;
	CreateViewport(clientWidth, clientHeight);

	CreateBlendState();
	CreateConstantBuffer();
}

DXManager::~DXManager()
{
	if (constantBuffer) constantBuffer->Release();
	if (alphaBlendState) alphaBlendState->Release();
	if (backBufferTarget) backBufferTarget->Release();
	if (swapChain) swapChain->Release();
	if (deviceContext) deviceContext->Release();
	if (device) device->Release();
	
	constantBuffer = 0;
	alphaBlendState = 0;
	backBufferTarget = 0;
	swapChain = 0;
	deviceContext = 0;
	device = 0;
}

void DXManager::BeginFrame()
{
	// BLUE: 0.4f, 0.6f, 0.75f, 1.0f
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	deviceContext->ClearRenderTargetView(backBufferTarget, color);
}

void DXManager::EndFrame()
{
	swapChain->Present(0, 0);
}

ID3D11Device* DXManager::GetDevice()
{
	return device;
}

ID3D11DeviceContext* DXManager::GetDeviceContext()
{
	return deviceContext;
}

ID3D11Buffer* DXManager::GetConstantBuffer()
{
	return constantBuffer;
}

#pragma region Creation Methods
bool DXManager::CreateDeviceAndSwapChain(HWND hwnd, unsigned int width, unsigned int height)
{
	// Specifying driver types
	const D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_SOFTWARE,
	};
	const unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

	// Specifying feature levels
	const D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	const unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);

	// Swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	// Create device, context and swap chain
	HRESULT result;
	for (unsigned int driver = 0; driver < totalDriverTypes; driver++)
	{
		result = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[driver], nullptr,
			creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION,
			&swapChainDesc, &swapChain, &device, &featureLevel, &deviceContext);

		if (SUCCEEDED(result))
		{
			driverType = driverTypes[driver];
			return true;
		}
	}

	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to create the Direct3D device!", L"Error!", MB_OK);
		PostQuitMessage(0);
	}

	return false;
}

bool DXManager::CreateRenderTargetView()
{
	ID3D11Texture2D* backBufferTexture;

	HRESULT result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&backBufferTexture);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to get the swap chain back buffer!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return false;
	}

	result = device->CreateRenderTargetView(backBufferTexture, 0,
		&backBufferTarget);

	if (backBufferTexture)
	{
		backBufferTexture->Release();
	}

	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to create the render target view!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return false;
	}

	deviceContext->OMSetRenderTargets(1, &backBufferTarget, 0);
	return true;
}

void DXManager::CreateViewport(unsigned int width, unsigned int height)
{
	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 0.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	deviceContext->RSSetViewports(1, &viewport);
}

void DXManager::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;
	
	HRESULT d3dResult = device->CreateBlendState(&blendDesc, &alphaBlendState);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating blend state!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	const float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(alphaBlendState, blendFactor, 0xFFFFFFFF);
}

void DXManager::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC constDesc;
	ZeroMemory(&constDesc, sizeof(constDesc));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(VSConstantBufferData);
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT d3dResult = device->CreateBuffer(&constDesc, 0, &constantBuffer);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error constant buffer!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
}
#pragma endregion Creating DirectX objects
