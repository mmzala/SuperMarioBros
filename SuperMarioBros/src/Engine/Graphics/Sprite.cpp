#include "Sprite.h"
#include <d3d11.h>
#include "Geometry/Quad.h"
#include "Texture2D.h"
#include "../SMBEngine.h" // Getting enigne
#include "DXManager.h" // Getting graphics
#include "Camera.h" // GetViewportProjectionMatrix()
#include "Shaders/Shader.h"

Sprite::Sprite(const char* textureFile, int spriteSheetSize)
	:
	VSCBData(new VSConstantBufferData(spriteSheetSize)),
	texture(new Texture2D(textureFile)),
	quad(new Quad(GetSize()))
{}

Sprite::~Sprite()
{
	delete VSCBData;
	delete texture;
	delete quad;
}

void Sprite::Draw(DirectX::XMMATRIX worldMatrix)
{
	unsigned int stride = quad->GetSizeOfVertex();
	unsigned int offset = 0;

	Shader* shader = SMBEngine::GetInstance()->GetSpriteShader();
	ID3D11DeviceContext* deviceContext = SMBEngine::GetInstance()->GetGraphics()->GetDeviceContext();

	deviceContext->IASetInputLayout(shader->GetInputLayout());
	deviceContext->IASetVertexBuffers(0, 1, quad->GetVertexBufferPP(), &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->VSSetShader(shader->GetVertexShader(), 0, 0);
	deviceContext->PSSetShader(shader->GetPixelShader(), 0, 0);

	deviceContext->PSSetShaderResources(0, 1, texture->GetShaderResourceViewPP());
	deviceContext->PSSetSamplers(0, 1, texture->GetSamplerStatePP());

	UpdateConstantBuffer(worldMatrix);

	// Drawing a quad, so 6 vertecies
	deviceContext->Draw(6, 0);
}

void Sprite::SetFrame(int frame)
{
	VSCBData->frame = frame;
}

int Sprite::GetFrame()
{
	return VSCBData->frame;
}

DirectX::XMFLOAT2 Sprite::GetSize()
{
	return DirectX::XMFLOAT2((float)(texture->GetWidth() / VSCBData->sheetSize), 
		(float)(texture->GetHeight() / VSCBData->sheetSize));
}

void Sprite::UpdateConstantBuffer(DirectX::XMMATRIX worldMatrix)
{
	ID3D11DeviceContext* deviceContext = SMBEngine::GetInstance()->GetGraphics()->GetDeviceContext();

	DirectX::XMMATRIX mvp = DirectX::XMMatrixMultiply(worldMatrix, SMBEngine::GetInstance()->GetCamera()->GetViewportProjectionMatrix());
	VSCBData->transform = DirectX::XMMatrixTranspose(mvp);

	deviceContext->UpdateSubresource(SMBEngine::GetInstance()->GetGraphics()->GetConstantBuffer(), 0, 0, VSCBData, 0, 0);
}
