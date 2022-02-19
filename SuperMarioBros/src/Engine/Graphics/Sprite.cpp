#include "Sprite.h"
#include <d3d11.h>
#include "Geometry/Quad.h"
#include "Texture2D.h"
#include "../SMBEngine.h" // Getting enigne
#include "DXManager.h" // Getting graphics
#include "Camera.h" // GetViewportProjectionMatrix()

Sprite::Sprite(SpriteSettings settings)
	:
	VSCBData(new VSConstantBufferData(settings.spriteSheetSize)),
	texture(new Texture2D(settings.textureFile)),
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

	ID3D11DeviceContext* deviceContext = SMBEngine::GetInstance()->GetGraphics()->GetDeviceContext();
	deviceContext->IASetVertexBuffers(0, 1, quad->GetVertexBufferPP(), &stride, &offset);

	deviceContext->PSSetShaderResources(0, 1, texture->GetShaderResourceViewPP());
	deviceContext->PSSetSamplers(0, 1, texture->GetSamplerStatePP());

	UpdateConstantBuffer(worldMatrix, deviceContext);

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

void Sprite::UpdateConstantBuffer(DirectX::XMMATRIX worldMatrix, ID3D11DeviceContext* deviceContext)
{
	DirectX::XMMATRIX mvp = DirectX::XMMatrixMultiply(worldMatrix, SMBEngine::GetInstance()->GetCamera()->GetViewportProjectionMatrix());
	VSCBData->transform = DirectX::XMMatrixTranspose(mvp);

	deviceContext->UpdateSubresource(SMBEngine::GetInstance()->GetGraphics()->GetConstantBuffer(), 0, 0, VSCBData, 0, 0);
}
