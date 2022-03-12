#pragma once

#include <DirectXMath.h> // XMMATRIX and XMINT2

class Texture2D;
class Quad;
struct VSConstantBufferData;
struct ID3D11DeviceContext;

struct SpriteSettings
{
	const char* textureFile;
	DirectX::XMINT2 spriteSheetSize;

	/// <summary>
	/// Creates settings, which decide how the sprite will function.
	/// </summary>
	/// <param name="textureFile">: What texture file to use </param>
	/// <param name="spriteSheetSize">: Sprite sheet size that contains 2^n animation frames (example: size 2 == 4 frames / size 3 == 9 frames) </param>
	SpriteSettings(const char* textureFile = nullptr, DirectX::XMINT2 spriteSheetSize = DirectX::XMINT2(1, 1))
		:
		textureFile(textureFile),
		spriteSheetSize(spriteSheetSize)
	{}
};

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

