#include "Sprite.h"
#include <d3d11.h>
#include "Geometry/Quad.h"
#include "Texture2D.h"
#include "../SMBEngine.h" // Getting enigne
#include "DXManager.h" // Getting graphics
#include "Camera.h" // GetViewportProjectionMatrix()
#include "Shaders/Shader.h"

Sprite::Sprite(const char* textureFile)
	:
	constantBuffer(nullptr),
	alphaBlendState(nullptr),
	texture(new Texture2D(textureFile)),
	quad(new Quad(DirectX::XMFLOAT2((float)texture->GetWidth(), (float)texture->GetHeight())))
{
	DXManager* graphics = SMBEngine::GetInstance()->GetGraphics();
	CreateConstantBuffer(graphics->GetDevice());
	CreateBlendState(graphics);
}

Sprite::~Sprite()
{
	delete texture;
	delete quad;

	if (constantBuffer) constantBuffer->Release();
	if (alphaBlendState) alphaBlendState->Release();

	constantBuffer = 0;
	alphaBlendState = 0;
}

void Sprite::Draw(DirectX::XMMATRIX worldMatrix)
{
	unsigned int stride = quad->GetSizeOfVertex();
	unsigned int offset = 0;

	Shader* shader = SMBEngine::GetInstance()->GetTextureShader();
	ID3D11DeviceContext* deviceContext = SMBEngine::GetInstance()->GetGraphics()->GetDeviceContext();

	deviceContext->IASetInputLayout(shader->GetInputLayout());
	deviceContext->IASetVertexBuffers(0, 1, quad->GetVertexBufferPP(), &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->VSSetShader(shader->GetVertexShader(), 0, 0);
	deviceContext->PSSetShader(shader->GetPixelShader(), 0, 0);

	deviceContext->PSSetShaderResources(0, 1, texture->GetShaderResourceViewPP());
	deviceContext->PSSetSamplers(0, 1, texture->GetSamplerStatePP());

	DirectX::XMMATRIX mvp = DirectX::XMMatrixMultiply(worldMatrix, SMBEngine::GetInstance()->GetCamera()->GetViewportProjectionMatrix());
	mvp = DirectX::XMMatrixTranspose(mvp);

	deviceContext->UpdateSubresource(constantBuffer, 0, 0, &mvp, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

	// Drawing a quad, so 6 vertecies
	deviceContext->Draw(6, 0);
}

void Sprite::CreateConstantBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC constDesc;
	ZeroMemory(&constDesc, sizeof(constDesc));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT d3dResult = device->CreateBuffer(&constDesc, 0, &constantBuffer);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error constant buffer!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
}

void Sprite::CreateBlendState(DXManager* graphics)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	const float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	HRESULT d3dResult = graphics->GetDevice()->CreateBlendState(&blendDesc, &alphaBlendState);

	if (FAILED(d3dResult))
	{
		MessageBox(NULL, L"Error creating blend state!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	graphics->GetDeviceContext()->OMSetBlendState(alphaBlendState, blendFactor, 0xFFFFFFFF);
}
