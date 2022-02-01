struct VSOut
{
	float4 pos : SV_Position;
	float2 tex0 : TEXCOORD0;
};

VSOut main(float3 pos : POSITION, float2 tex0 : TEXCOORD0)
{
	VSOut vso;
	vso.pos = float4(pos, 1.0f);
	vso.tex0 = tex0;
	return vso;
}