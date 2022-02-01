#include "Sprite.h"
#include <d3d11.h>
#include "Geometry/Quad.h"
#include "Texture2D.h"

Sprite::Sprite(const char* textureFile, ID3D11Device* device)
	:
	quad(new Quad(device)),
	texture(new Texture2D(textureFile, device))
{}

Sprite::~Sprite()
{
	delete texture;
	delete quad;
}

void Sprite::Draw(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride = quad->GetSizeOfVertex();
	unsigned int offset = 0;

	deviceContext->IASetInputLayout(quad->GetInputLayout());
	deviceContext->IASetVertexBuffers(0, 1, quad->GetVertexBufferPP(), &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->VSSetShader(quad->GetVertexShader(), 0, 0);
	deviceContext->PSSetShader(quad->GetPixelShader(), 0, 0);

	deviceContext->PSSetShaderResources(0, 1, texture->GetShaderResourceViewPP());
	deviceContext->PSSetSamplers(0, 1, texture->GetSamplerStatePP());

	// Drawing a quad, so 6 vertecies
	deviceContext->Draw(6, 0);
}
