// Jake

struct Input
{
	float4 positionCS 	: SV_Position;
	float4 positionWS 	: POSITION;
	float3 normal 		: NORMAL;
	float  zvalue  		: ZVALUE;
};

struct Output
{
	// Environment Map Generation
	float4 position : SV_Position;
	float  zvalue  	: ZVALUE;
	uint   rtaindex : SV_RenderTargetArrayIndex;
	
	// GBuffer Generation
	float4 positionWS 	: POSITION;
	float3 normal 		: NORMAL;
};

[maxvertexcount(3)]
[instance(2)]
void main(	triangle Input input[3],
			uint id : SV_GSInstanceID,
            inout TriangleStream<Output> OutputStream )
{
	Output output;

	// Initialize the vertex order and the direction of the paraboloid.
	uint3 order = uint3( 0, 1, 2 );
	float direction = 1.0f;

	// Check to see which copy of the primitive this is.  If it is 0, then it
	// is considered the front facing paraboloid.  If it is 1, then it is
	// considered the back facing paraboloid.  For back facing, we reverse
	// the output vertex winding order.
	if ( id == 1 )
	{
		order.xyz = order.xzy;
		direction = -1.0f;
	}

    // Emit three vertices for one complete triangle.
    for ( int i = 0; i < 3; i++ )
    {
		// Create a projection factor, which determines which half space 
		// will be considered positive and also adds the viewing vector
		// which is (0,0,1) and hence can only be added to the z-component.
		float projFactor 		= input[order[i]].zvalue * direction + 1.0f;
		output.positionCS.x 	= input[order[i]].positionCS.x / projFactor;
		output.positionCS.y 	= input[order[i]].positionCS.y / projFactor;
		output.positionCS.z 	= input[order[i]].positionCS.z;
		output.positionCS.w 	= 1.0f;

		// Simply use the geometry shader instance as the render target
		// index for this primitive.
		output.rtaindex = id;
		output.zvalue 	= input[order[i]].zvalue * direction;
		
		// GBuffer Generation
		ouput.positionWS 	= input[order[i]].positionWS;
		ouput.normal 		= input[order[i]].normal;

		// Write the vertex to the output stream.
        OutputStream.Append(output);
    }

	OutputStream.RestartStrip();
}