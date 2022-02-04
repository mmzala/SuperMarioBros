cbuffer CBuffer
{
	matrix transform;
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
	vso.tex0 = tex0;
	return vso;
}