#include "WorldViewProjData.h"

#include <d3d11.h>
#include <xnamath.h>

#include "Camera.h"

WorldViewProjData::WorldViewProjData( const IConstantVariableData&worldData, Camera *camera ) : IConstantVariableData{ camera }, mWorldData{ &worldData }
{
	//memcpy( &xmWorld, world, sizeof( xmWorld ) );
}

void *WorldViewProjData::operator()() const
{
	if ( mData )
	{
		memcpy( &xmWorld, (*mWorldData)(), sizeof( xmWorld ) );

		CXMMATRIX world{ XMLoadFloat4x4( &xmWorld ) };
		CXMMATRIX viewProj{ static_cast<Camera *>( mData )->GetViewProj() };
		XMStoreFloat4x4( &xmWorldViewProj, XMMatrixTranspose( viewProj ) * world );
		
		return &xmWorldViewProj;
	}
	else
	{
		return &xmWorld;
	}
}