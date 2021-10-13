#include "WorldViewData.h"

#include <d3d11.h>
#include <xnamath.h>

#include "Camera.h"

WorldViewData::WorldViewData( const IConstantVariableData &worldData, Camera *camera ) : IConstantVariableData{ camera }, mWorldData{ &worldData }
{
	//memcpy( &xmWorld, world, sizeof( xmWorld ) );
}

void * WorldViewData::operator()() const
{
	if ( mData )
	{
		memcpy( &xmWorld, (*mWorldData)(), sizeof( xmWorld ) );

		CXMMATRIX world{ XMLoadFloat4x4( &xmWorld ) };
		CXMMATRIX view{ static_cast<Camera *>( mData )->GetView() };
		XMStoreFloat4x4( &xmWorldView, XMMatrixTranspose( view ) * world );
		
		return &xmWorldView;
	}
	else
	{
		return &xmWorld;
	}
}