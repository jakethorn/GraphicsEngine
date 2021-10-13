#include "VertexShaderStage.h"

#include <d3d11shader.h>

#include "Common.h"
#include "Factory.h"
#include "InputLayout.h"

/*
	HELPER FUNCTIONS
*/

#define powi(x, y) (int)powf((float)x, (float)y)

void CreateInputLayout( UINT bitset, D3D11_INPUT_ELEMENT_DESC *outIed, UINT &outCount )
{
	outCount = 0;

	for (int i = 0; i < inputlayout::NUM_STD_ELEMENTS; i++)
	{
		if (bitset & powi(2, i))
		{
			outIed[i] = inputlayout::STD_ELEMENT[outCount];
			outIed[i].InputSlot = outCount;

			outCount++;
		}
	}
}

/*
	CLASS DEFINITIONS
*/

VertexShaderStage::VertexShaderStage( string name, UINT inputLayoutBitset )
{	
	// Input layout
	D3D11_INPUT_ELEMENT_DESC	ied[inputlayout::NUM_STD_ELEMENTS];		
	UINT						elementCount;				

	CreateInputLayout( inputLayoutBitset, ied, elementCount );	

	// Vertex shader
	std::wstring wname;
	wname.assign( name.begin(), name.end() );

	wstring file = L"../../../Shared/Shaders/" + wname + L".vs";

	factory::CreateVertexShaderAndInputLayoutFromFile( file.c_str(), "main", &ied[0], elementCount, &mShader, &mInputLayout, &mReflection );

	//Init constant buffers
	InitConstantBuffers();
}

VertexShaderStage::~VertexShaderStage()
{
	ReleaseCOM( mInputLayout );
}

void VertexShaderStage::Restore()
{
	mContext->VSSetShader( mShader, 0, 0 );

	mContext->VSSetConstantBuffers	( 0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1, mConstantBuffers );
	mContext->VSSetSamplers			( 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1,				mSamplers );
	mContext->VSSetShaderResources	( 0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1,		mShaderResources );
	
	mContext->IASetInputLayout( mInputLayout );
}

void VertexShaderStage::SetPrimaryShaderResource( int slot )
{
	mContext->VSSetShaderResources(0, 1, &mShaderResources[slot]);
}