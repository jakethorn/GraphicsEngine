// Mega

struct Input
{
	float3 position : POSITION;
};

struct Output
{
	float4 position : SV_Position;
	float2 texcoord : TEXCOORD;
};

Output main(Input input)
{
	Output output;
	
	output.position = float4(input.position, 1.0f);
	output.texcoord = (float2(input.position.x, -input.position.y) + 1.0f) / 2.0f;
	
	return output;
}

