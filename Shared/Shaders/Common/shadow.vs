// Mega

cbuffer PerFrame : register(cb0)
{
	float4x4 gWorldViewProj;
};

float4 main(float3 position : POSITION) : SV_Position
{
	return mul(float4(position, 1.0f), gWorldViewProj);
}