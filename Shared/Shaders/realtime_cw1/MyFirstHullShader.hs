// Mega

struct Input
{
	float4 positionCS 	: SV_Position;
	float4 positionWS 	: POSITION;
	float3 normal 		: NORMAL;
};

struct Output
{
	float4 positionWS 	: POSITION;
	float3 normal 		: NORMAL;
};

struct HSPatchData 
{
	float EdgeTessFactor[4]		: SV_TessFactor;
	float InsideTessFactor[2]	: SV_InsideTessFactor;
};

HSPatchData CalcHSPatchConstants(	InputPatch<Input, 4> ip, 
									uint patchID : SV_PrimitiveID) 
{
	HSPatchData P;

	// Calculate edge tessellation factors for quad
	P.EdgeTessFactor[0] = 3;
	P.EdgeTessFactor[1] = 7;
	P.EdgeTessFactor[2] = 11;
	P.EdgeTessFactor[3] = 15;

	// Calculate internal tessellation factors along u and v in quad domain
	P.InsideTessFactor[0] = 15;
	P.InsideTessFactor[1] = 15;

	return P;
}

[domain("quad")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")] // Make sure cp's are addressed correctly wrt. uv
[outputcontrolpoints(4)]
[patchconstantfunc("CalcHSPatchConstants")]
Output main(	InputPatch<Input, 4> input,
				uint i : SV_OutputControlPointID,
				uint patchID : SV_PrimitiveID)
{
	Output output;

	// Calculate output control point i (1:1 mapping with input for pass-through hull shader)
	output.positionWS 	= input[i].positionWS;
	output.normal 		= input[i].normal;

	return output;
}
