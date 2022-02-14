#pragma once

#include <DirectXMath.h> // XMMATRIX

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
	/// <param name="textureFile">: What texture file to use </param>
	/// <param name="spriteSheetSize">: Sprite sheet size that contains 2^n animation frames (example: size 2 == 4 frames / size 3 == 9 frames) </param>
	Sprite(const char* textureFile, int spriteSheetSize = 1);
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

struct Animation
{
	int startFrame;
	int endFrame;
	// Animation frames per second
	float speed;

	Animation(int startFrame, int endFrame, float speed)
		:
		startFrame(startFrame),
		endFrame(endFrame),
		speed(speed)
	{}
};

