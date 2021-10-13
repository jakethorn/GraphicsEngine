#include "WorldInverseTransposeData.h"

#include <d3d11.h>
#include <xnamath.h>

#include "Camera.h"

WorldInverseTransposeData::WorldInverseTransposeData( const IConstantVariableData &worldData ) : IConstantVariableData{ nullptr }, mWorldData{ &worldData }
{
	//memcpy( &xmWorld, world, sizeof( xmWorld ) );
}

void *WorldInverseTransposeData::operator()() const
{
	memcpy( &xmWorld, (*mWorldData)(), sizeof( xmWorld ) );

	CXMMATRIX world{ XMLoadFloat4x4( &xmWorld ) };
		
	XMVECTOR *a = new XMVECTOR();
	CXMMATRIX worldInvTrn = XMMatrixInverse( a, XMMatrixTranspose( world ) );

	XMStoreFloat4x4( &xmWorld, worldInvTrn );
		
	return &xmWorld;
}