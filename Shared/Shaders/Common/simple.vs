// Mega

cbuffer PerFrame : register(cb0)
{
	float4x4 gWorld;
	float4x4 gWorldInvTrn;
	float4x4 gWorldViewProj;
	float4x4 gShadowTex;
};

struct Input
{
	float3 position : POSITION;
	float3 normal	: NORMAL;
};

struct Output
{
	float4 positionCS 	: SV_Position;
	float4 positionWS 	: POSITION;
	float3 normal 		: NORMAL;
	float4 positionTS	: TEXCOORD;
};

Output main(Input input)
{
	Output output;
	
	output.positionCS 	= mul(float4(input.position, 1.0f), gWorldViewProj);
	output.positionWS 	= mul(float4(input.position, 1.0f), gWorld);
	output.normal 		= mul(input.normal, (float3x3)gWorldInvTrn);
	output.positionTS	= mul(float4(input.position, 1.0f), gShadowTex);
	
	return output;
}

