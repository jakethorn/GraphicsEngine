#include "OscillateWorldData.h"

#include <cmath>

OscillateWorldData::OscillateWorldData( const void *const data ) : IConstantVariableData{ data, sizeof(XMFLOAT4X4) }
{
	memcpy( &mWorld, data, sizeof(XMFLOAT4X4) );
}

void *OscillateWorldData::operator()() const
{
	// load
	XMMATRIX world = XMLoadFloat4x4( &mWorld );
	world = XMMatrixTranspose( world );

	// rotate
	static float translation = -1.5f;
	translation += 0.00025;
	world *= XMMatrixTranslation( 0.0f, sinf( translation ) / 360.0f, 0.0f );

	// store
	world = XMMatrixTranspose( world );
	XMStoreFloat4x4( &mWorld, world );

	return &mWorld;
}