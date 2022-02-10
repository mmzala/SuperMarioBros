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
	texture(new Texture2D(textureFile)),
	quad(new Quad(GetSize()))
{}

Sprite::~Sprite()
{
	delete texture;
	delete quad;
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

	ID3D11Buffer* constantBuffer = SMBEngine::GetInstance()->GetGraphics()->GetConstantBuffer();
	deviceContext->UpdateSubresource(constantBuffer, 0, 0, &mvp, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

	// Drawing a quad, so 6 vertecies
	deviceContext->Draw(6, 0);
}

DirectX::XMFLOAT2 Sprite::GetSize()
{
	return DirectX::XMFLOAT2((float)texture->GetWidth(), (float)texture->GetHeight());
}
