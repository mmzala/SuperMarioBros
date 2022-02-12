cbuffer CBuffer
{
	matrix transform;
	int sheetSize; // Sprite sheet size that contains 2^n animation frames (example: size 2 == 4 frames / size 3 == 9 frames)
	int frame; // Which part of the texutre is to be displayed
};

struct VSOut
{
	float4 pos : SV_Position;
	float2 tex0 : TEXCOORD0;
};

VSOut main(float3 pos : POSITION, float2 tex0 : TEXCOORD0)
{
	VSOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform);

	float zoom;
	zoom = 1.0 / sheetSize;
	vso.tex0 = tex0 * zoom;
	vso.tex0 += float2(zoom * (frame % sheetSize), zoom * floor(frame / sheetSize));

	return vso;
}