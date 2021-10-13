#include "HullShaderStage.h"

#include <d3d11shader.h>

#include "Factory.h"

/*
	CLASS DEFINITIONS
*/

HullShaderStage::HullShaderStage( string name )
{	
	if ( name != "" )
	{
		std::wstring wname;
		wname.assign( name.begin(), name.end() );

		wstring file = L"../../../Shared/Shaders/" + wname + L".hs";

		mShader = factory::CreateHullShaderFromFile( file.c_str(), "main", &mReflection );

		//Init constant buffers
		InitConstantBuffers();
	}
}

void HullShaderStage::Restore()
{
	mContext->HSSetShader( mShader, 0, 0 );

	mContext->HSSetConstantBuffers	( 0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1, mConstantBuffers );
	mContext->HSSetSamplers			( 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1,				mSamplers );
	mContext->HSSetShaderResources	( 0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1,		mShaderResources );
}

void HullShaderStage::SetPrimaryShaderResource( int slot )
{
	mContext->HSSetShaderResources(0, 1, &mShaderResources[slot]);
}