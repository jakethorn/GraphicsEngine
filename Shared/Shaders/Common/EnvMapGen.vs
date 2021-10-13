// Jake

cbuffer PerFrame : register(cb0)
{
	float4x4 gWorld;
	float4x4 gWorldInvTrn;
	float4x4 gWorldView;
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
	float  zvalue  		: ZVALUE;
};

Output main( Input input )
{
    Output output;
	
	// Environment Map Generation
	output.positionCS = mul( float4( input.positionCS, 1 ), gWorldView );
	float L = length( output.positionCS.xyz );
	output.positionCS = output.positionCS / L;
	output.zvalue = output.positionCS.z;
	output.positionCS.z = L / 500;
	output.positionCS.w = 1;
	
	// GBuffer Generation
	output.positionWS 	= mul(float4(input.position, 1.0f), gWorld);
	output.normal 		= mul(input.normal, (float3x3)gWorldInvTrn);
	
	return output;
}