// Mega

cbuffer PerFrame
{
	float4x4 gWorldViewProj;
};

struct Output
{
	float4 positionCS : SV_POSITION;
    float3 positionOS : POSITION;
};
 
Output main(float3 position : POSITION)
{
	Output output;
	
	output.positionCS = mul(float4(position, 1.0f), gWorldViewProj);
	output.positionOS = position;
	
	return output;
}