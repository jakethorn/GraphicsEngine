#include "IShaderStage.h"

template<typename T>
void IShaderStage<T>::InitConstantBuffers()
{
	// get shader file description
	D3D11_SHADER_DESC sd;
	mReflection->GetDesc( &sd );

	// for each constant buffer in the shader file
	for ( UINT i = 0; i < sd.ConstantBuffers; ++i )
	{
		// get constant buffer description
		D3D11_SHADER_BUFFER_DESC sbd;
		mReflection->GetConstantBufferByIndex( i )->GetDesc( &sbd );

		// create direct3d and data buffers with appropriate sizes
		mConstantBuffers[i]		= factory::CreateConstantBuffer( true, NULL, sbd.Size );
		mConstantBufferData[i]	= new byte[sbd.Size];
		
		// for each variable in the constant buffers
		for (int j = 0; j < sbd.Variables; ++j)
		{
			// get the variable description
			D3D11_SHADER_VARIABLE_DESC svd;
			mReflection->GetConstantBufferByIndex(i)->GetVariableByIndex(j)->GetDesc(&svd);

			// create matching constant variable, storing offset, size and buffer number
			mConstantVariables[svd.Name] = ConstantVariable{ svd.StartOffset, svd.Size, i };
		}
	}
}