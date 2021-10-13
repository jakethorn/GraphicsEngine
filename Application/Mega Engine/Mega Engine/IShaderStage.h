// Mega

#pragma once

#ifndef SHADER_STAGE_H
#define SHADER_STAGE_H

#include <d3d11.h>
#include <d3d11shader.h>
#include <map>
#include <string>

#include "Common.h"
#include "Direct3D.h"
#include "IConstantVariableData.h"

class IConstantVariableData;

using std::map;
using std::string;

struct ConstantVariable
{
	unsigned int offset;
	unsigned int length;
	unsigned int bufferSlot;
};

template<typename T>
class IShaderStage
{
public:
	IShaderStage() : mContext{ d3d::GetImmediateContext() }
	{
		// Null out samplers and shader resources
		Nullify(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT,			mSamplers);			
		Nullify(D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT,	mShaderResources);	
	}

	virtual ~IShaderStage()
	{
		// release shader
		ReleaseCOM( mShader );

		// release constant buffers
		for ( int i = 0; i < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i )
		{
			ReleaseCOM( mConstantBuffers[i] );
			delete mConstantBufferData[i];
		}

		// release samplers
		for ( int i = 0; i < D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT; ++i )
			ReleaseCOM( mSamplers[i] );

		// release shader resources
		for ( int i = 0; i < D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i )
			ReleaseCOM( mShaderResources[i] );

		// release cached variables
		ReleaseCOM( mContext );
		ReleaseCOM( mReflection );
	}

	bool HasConstantVariable( string variableName )
	{
		return mConstantVariables.find( variableName ) != mConstantVariables.end();
	}
	
	void SetSamplers(UINT startSlot, UINT numSamplers, ID3D11SamplerState *const *samplers)	
	{ 
		Save(startSlot, numSamplers, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, samplers, mSamplers);			
	}

	void SetSampler(ID3D11SamplerState *samplers)	
	{ 
		Save(0, 1, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, &samplers, mSamplers);			
	}

	void SetShaderResources(UINT startSlot, UINT numResources, ID3D11ShaderResourceView *const *resources)	
	{ 
		Save(startSlot, numResources, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT,	resources, mShaderResources);	
	}
	
	bool UpdateConstantVariable( string variableName, IConstantVariableData *cvd )
	{
		// return false if we dont have this variable in the constant buffer
		auto a = mConstantVariables.find(variableName);
		if (a == mConstantVariables.end())
			return false;

		// update variable in the constant buffer
		ConstantVariable r = a->second;

		memcpy(mConstantBufferData[r.bufferSlot] + r.offset, (*cvd)()/* <- functor */, r.length);
		mContext->UpdateSubresource(mConstantBuffers[r.bufferSlot], 0, NULL, mConstantBufferData[r.bufferSlot], 0, 0);

		// we had the variable in the constant buffer
		return true;
	}

	virtual void Restore() = 0;
	virtual void SetPrimaryShaderResource( int slot ) = 0;
	
protected:
	T *mShader;
	
	map<string, ConstantVariable>		mConstantVariables;															// Map of constant buffer variables in shader
	ID3D11Buffer						*mConstantBuffers	[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];	// Direct 3D constant buffers
	byte								*mConstantBufferData[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];	// Buffer data

	ID3D11SamplerState					*mSamplers			[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];				// Shader sampler states
	ID3D11ShaderResourceView			*mShaderResources	[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];			// Shader resource views
	
	ID3D11DeviceContext					*mContext;																	// Cached immediate context
	ID3D11ShaderReflection				*mReflection;																// Cached shader reflection

	void InitConstantBuffers()
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

private:
	template<typename T>
	void Save( UINT start, UINT numFroms, UINT end, T * const *from, T **to )
	{
		for ( int i = 0; i < end; i++ )
		{
			// for all saving elements
			if ( i >= start && i < start + numFroms )
			{
				// save
				to[i] = from[i - start];
				to[i]->AddRef();
			}
			else
			{
				// set to null
				to[i] = NULL;
			}
		}
	}
	
	template<typename T>
	void Nullify( UINT size, T **to )
	{
		for ( int i = 0; i < size; i++ )
			to[i] = NULL;
	}
};

#endif /* SHADER_STAGE_H */