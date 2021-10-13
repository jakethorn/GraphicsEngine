#include "DomainShaderStage.h"

#include <d3d11shader.h>

#include "Factory.h"

/*
	CLASS DEFINITIONS
*/

DomainShaderStage::DomainShaderStage( string name )
{	
	if ( name != "" )
	{
		std::wstring wname;
		wname.assign( name.begin(), name.end() );

		wstring file = L"../../../Shared/Shaders/" + wname + L".ds";

		mShader = factory::CreateDomainShaderFromFile( file.c_str(), "main", &mReflection );

		//Init constant buffers
		InitConstantBuffers();
	}
}

void DomainShaderStage::Restore()
{
	mContext->DSSetShader( mShader, 0, 0 );

	mContext->DSSetConstantBuffers	( 0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1, mConstantBuffers );
	mContext->DSSetSamplers			( 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1,				mSamplers );
	mContext->DSSetShaderResources	( 0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1,		mShaderResources );
}

void DomainShaderStage::SetPrimaryShaderResource( int slot )
{
	mContext->DSSetShaderResources(0, 1, &mShaderResources[slot]);
}