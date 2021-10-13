#include "UnstructuredFunctions.h"

#include "Common.h"
#include "Factory.h"

void *GetBufferData(ID3D11Device * const device, ID3D11Buffer *buffer, UINT byteWidth)
{
	// make a staging buffer
	ID3D11Buffer *stagingBuffer = factory::CreateStagingBuffer(byteWidth);

	// get immediate context
	ID3D11DeviceContext *context;
	device->GetImmediateContext(&context);

	// copy contents of the provided buffer into the newly created one
	context->CopyResource(stagingBuffer, buffer);

	// read the contents of the new buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	context->Map(stagingBuffer, 0, D3D11_MAP_READ, 0, &ms);

	void *data = new float[byteWidth / sizeof(float)];
	memcpy(data, ms.pData, byteWidth);

	// unmap that shit
	context->Unmap(stagingBuffer, 0);

	ReleaseCOM(context);
	ReleaseCOM(stagingBuffer);

	// return to user
	return data;
}

std::wstring help::ToWString( std::string text )
{
	std::wstring retval;
	retval.assign( text.begin(), text.end() );

	return retval;
}