#pragma once

#include <DirectXMath.h> // XMMATRIX and XMINT2
#include "../../Game/Settings/SpriteSettings.h"

class Texture2D;
class Quad;
struct VSConstantBufferData;
struct ID3D11DeviceContext;

class Sprite
{
public:
	/// <summary>
	/// Creates a sprite with own texture2D and Quad
	/// </summary>
	Sprite(SpriteSettings settings);
	~Sprite();

	void Draw(DirectX::XMMATRIX worldMatrix);

	/// <summary>
	/// Sets animation frame
	/// </summary>
	/// <param name="frame">: What frame to display on the sprite sheet </param>
	void SetFrame(int frame);

	/// <summary>
	/// Gets current animation frame
	/// </summary>
	/// <returns> Current animation frame </returns>
	int GetFrame();

	/// <summary>
	/// Allows to flip the sprite in the X axis
	/// </summary>
	/// <param name="value">: If sprite should be flipped on X axis</param>
	void FlipSpriteX(bool value);

	/// <summary>
	/// Returns the size of the rendered sprite
	/// </summary>
	/// <returns> Size of the rendered sprite </returns>
	DirectX::XMFLOAT2 GetSize();

private:
	void UpdateConstantBuffer(DirectX::XMMATRIX worldMatrix , ID3D11DeviceContext* deviceContext);

private:
	// Constant buffer data
	VSConstantBufferData* VSCBData;

	Texture2D* texture;
	Quad* quad;

	DirectX::XMFLOAT2 sheetSize;
};

