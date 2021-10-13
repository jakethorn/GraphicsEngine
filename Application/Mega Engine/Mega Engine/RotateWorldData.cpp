#include "RotateWorldData.h"

RotateWorldData::RotateWorldData( const void *const data ) : IConstantVariableData{ data, sizeof(XMFLOAT4X4) }
{
	memcpy( &mWorld, data, sizeof(XMFLOAT4X4) );
}

void *RotateWorldData::operator()() const
{
	// load
	XMMATRIX world = XMLoadFloat4x4( &mWorld );
	world = XMMatrixTranspose( world );

	// rotate
	world *= XMMatrixRotationY( 0.001f );

	// store
	world = XMMatrixTranspose( world );
	XMStoreFloat4x4( &mWorld, world );

	return &mWorld;
}