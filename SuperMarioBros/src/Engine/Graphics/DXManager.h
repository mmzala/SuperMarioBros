#pragma once

#include <d3d11.h> // DirectX classes
#include <DirectXMath.h> // XMMATRIX

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")

/// <summary>
/// Manages DirectX objects
/// </summary>
class DXManager
{
public:
	DXManager(HWND hwnd, const unsigned int clientWidth, const unsigned int clientHeight);
	~DXManager();

	void BeginFrame();
	void EndFrame();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	ID3D11Buffer* GetConstantBuffer();

private:
	bool CreateDeviceAndSwapChain(HWND hwnd, unsigned int width, unsigned int height);
	bool CreateRenderTargetView();
	void CreateViewport(unsigned int width, unsigned int height);

	void CreateBlendState();
	void CreateConstantBuffer();

private:
	 ID3D11Device* device;
	 ID3D11DeviceContext* deviceContext;
	 IDXGISwapChain* swapChain;
	 ID3D11RenderTargetView* backBufferTarget;

	 ID3D11Buffer* constantBuffer;
	 ID3D11BlendState* alphaBlendState;

	 D3D_DRIVER_TYPE driverType;
	 D3D_FEATURE_LEVEL featureLevel;
};

// Constant buffer data used for sprite rendering
struct VSConstantBufferData
{
	DirectX::XMMATRIX transform;
	int sheetSizeX;
	int sheetSizeY;
	int frame;
	BOOL flipSpriteX;

	VSConstantBufferData(DirectX::XMINT2 spriteSheetSize)
		:
		transform(DirectX::XMMATRIX()),
		sheetSizeX(spriteSheetSize.x),
		sheetSizeY(spriteSheetSize.y),
		frame(0),
		flipSpriteX(false)
	{}
};