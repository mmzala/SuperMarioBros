Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

struct PSInput
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
};

float4 main(PSInput frag) : SV_TARGET
{
	return colorMap.Sample(colorSampler, frag.tex0);
}