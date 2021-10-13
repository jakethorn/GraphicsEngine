#include "ShadowTexData.h"

#include "Camera.h"

ShadowTexData::ShadowTexData( const IConstantVariableData &worldData, Camera *camera ) : WorldViewProjData{ worldData, camera } {}

void * ShadowTexData::operator()() const
{
	if ( mData )
	{
		CXMMATRIX T{
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f
		};
		
		memcpy( &xmWorld, (*mWorldData)(), sizeof( xmWorld ) );

		CXMMATRIX world{ XMLoadFloat4x4( &xmWorld ) };
		CXMMATRIX viewProj{ static_cast<Camera *>( mData )->GetViewProj() };
		XMStoreFloat4x4( &xmWorldViewProj, XMMatrixTranspose( viewProj * T ) * world );
		
		return &xmWorldViewProj;
	}
	else
	{
		return &xmWorld;
	}
}