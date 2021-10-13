#include "IConstantVariableData.h"

#include <cstdlib>
#include <cstring>

IConstantVariableData::IConstantVariableData(void * const data) : mData{ data }
{

}

IConstantVariableData::IConstantVariableData(const void * const data, size_t size)
{
	if ( data && size )
	{
		mData = malloc( size );
		memcpy( mData, data, size );

		mHasOwnership = true;
	}
}

IConstantVariableData::~IConstantVariableData()
{
	if ( mHasOwnership )
		free( mData );
}

void * IConstantVariableData::operator()() const
{
	return mData;
}

void IConstantVariableData::operator()(void * const data)
{
	mData = data;
	mHasOwnership = false;
}
void IConstantVariableData::operator()(const void * const data, size_t size)
{
	if ( size )
	{
		mData = malloc( size );
		memcpy( mData, data, size );

		mHasOwnership = true;
	}
}