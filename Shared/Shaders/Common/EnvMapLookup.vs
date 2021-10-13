// Jake

cbuffer PerFrame : register(cb0)
{
	float3 		gCameraPos;
	float4x4 	gWorld;
	float4x4 	gWorldInvTrn;
	float4x4 	gWorldViewProj;
}

struct Input
{
    float3 position	: POSITION;
    float3 normal   : NORMAL;
};

struct Output
{
    float4 position : SV_Position;
	float3 normal   : NORMAL;
	float3 camera   : CAMERA;
};

Output main( Input input )
{
    Output output;

	// Find the world space position of the vertex.
	float4 worldPos	= mul( float4( input.position, 1 ), gWorld );

	// Output the clip space position for the rasterizer.
	output.position	= mul( float4( input.position, 1 ), gWorldViewProj );

	// Find world space normal and eye vectors.
	output.normal	= normalize( mul( input.normal, (float3x3)gWorldInvTrn ) );
	output.camera	= normalize( worldPos.xyz - gCameraPos );
	
	return output;
}