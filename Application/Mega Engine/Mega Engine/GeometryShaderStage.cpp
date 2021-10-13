#include "GeometryShaderStage.h"

#include <d3d11shader.h>

#include "Factory.h"

/*
	CLASS DEFINITIONS
*/

GeometryShaderStage::GeometryShaderStage( string name )
{	
	if ( name != "" )
	{
		std::wstring wname;
		wname.assign( name.begin(), name.end() );

		wstring file = L"../../../Shared/Shaders/" + wname + L".gs";

		mShader = factory::CreateGeometryShaderFromFile( file.c_str(), "main", &mReflection );

		//Init constant buffers
		InitConstantBuffers();
	}
}

void GeometryShaderStage::Restore()
{
	mContext->GSSetShader( mShader, 0, 0 );

	mContext->GSSetConstantBuffers	( 0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1, mConstantBuffers );
	mContext->GSSetSamplers			( 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1,				mSamplers );
	mContext->GSSetShaderResources	( 0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1,		mShaderResources );
}

void GeometryShaderStage::SetPrimaryShaderResource( int slot )
{
	mContext->GSSetShaderResources(0, 1, &mShaderResources[slot]);
}