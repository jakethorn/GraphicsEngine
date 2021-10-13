#include "PixelShaderStage.h"

#include <d3d11shader.h>

#include "Factory.h"

/*
	CLASS DEFINITIONS
*/

PixelShaderStage::PixelShaderStage( string name )
{	
	if ( name != "" )
	{
		std::wstring wname;
		wname.assign( name.begin(), name.end() );

		wstring file = L"../../../Shared/Shaders/" + wname + L".ps";

		mShader = factory::CreatePixelShaderFromFile( file.c_str(), "main", &mReflection );

		//Init constant buffers
		InitConstantBuffers();
	}
}

void PixelShaderStage::Restore()
{
	mContext->PSSetShader( mShader, 0, 0 );

	mContext->PSSetConstantBuffers	( 0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1, mConstantBuffers );
	mContext->PSSetSamplers			( 0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1,				mSamplers );
	mContext->PSSetShaderResources	( 0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1,		mShaderResources );
}

void PixelShaderStage::SetPrimaryShaderResource( int slot )
{
	mContext->PSSetShaderResources(0, 1, &mShaderResources[slot]);
}