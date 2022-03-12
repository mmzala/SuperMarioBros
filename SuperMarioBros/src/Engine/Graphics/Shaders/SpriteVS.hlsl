cbuffer CBuffer
{
	matrix transform;
	int sheetSizeX;
	int sheetSizeY;
	int frame; // Which part of the texutre is to be displayed
	bool flipSpriteX;
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

	float zoomX = 1.0f / sheetSizeX;
	float zoomY = 1.0f / sheetSizeY;

	vso.tex0.x = tex0.x * zoomX;
	vso.tex0.y = tex0.y * zoomY;

	if (flipSpriteX)
	{
		vso.tex0.x += zoomX * (sheetSizeX - frame - 1 % sheetSizeX);
		vso.tex0.x = -vso.tex0.x;
	}
	else
	{
		vso.tex0.x += zoomX * (frame % sheetSizeX);
	}
	vso.tex0.y += zoomY * floor(frame / sheetSizeY);

	// A very hacky way to fix a tex0.y going back a line when it's the first/last frame in the line
	if ((frame % sheetSizeX == 0 || 
		frame % sheetSizeX == sheetSizeX - 1) && 
		frame != 0 && 
		sheetSizeX < sheetSizeY)
	{
		vso.tex0.y += zoomY;
	}

	return vso;
}