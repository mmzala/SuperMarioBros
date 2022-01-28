#include <Windows.h>
#include <d3d11.h> // ID3D11Device and ID3D11DeviceContext
#include <dxgi.h> // IDXGISwapChain

/// <summary>
/// Used to render graphics on screen
/// </summary>
class DirectX
{
public:
	DirectX(HWND hwnd);
	~DirectX();

	void BeginFrame();
	void EndFrame();

private:
	/// <summary>
	/// Creates device, context and swap chain by calling "D3D11CreateDeviceAndSwapChain()"
	/// </summary>
	/// <param name="hwnd"> Hanlde to window </param>
	/// <param name="width"> Width of the client </param>
	/// <param name="height"> Height of the client </param>
	/// <returns> If the creation was successful or not </returns>
	bool CreateDeviceAndSwapChain(HWND hwnd, unsigned int width, unsigned int height);

	/// <summary>
	/// Creates and binds the render target view
	/// </summary>
	/// <returns> If the render target view was successfully created and binded </returns>
	bool CreateRenderTargetView();

	/// <summary>
	/// Creates full screen viewport
	/// </summary>
	/// <param name="width"> Width of the client </param>
	/// <param name="height"> Height of the clien </param>
	void CreateViewport(unsigned int width, unsigned int height);

private:
	 ID3D11Device* device;
	 ID3D11DeviceContext* deviceContext;
	 IDXGISwapChain* swapChain;
	 ID3D11RenderTargetView* backBufferTarget;

	 D3D_DRIVER_TYPE driverType;
	 D3D_FEATURE_LEVEL featureLevel;
};