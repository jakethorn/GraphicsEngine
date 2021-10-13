// Mega

cbuffer PerFrame : register(cb0)
{
	float4x4 gWorldViewProj;
};

struct Input
{
	float3 position : POSITION;
};

struct Output
{
	float4 positionCS : SV_Position;
};

Output main(Input input)
{
	Output output;
	
	output.positionCS 	= mul(float4(input.position, 1.0f), gWorldViewProj);
	
	return output;
}

