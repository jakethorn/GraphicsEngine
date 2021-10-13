#include "SkyBoxWVPData.h"

#include "Camera.h"

SkyBoxWVPData::SkyBoxWVPData( const IConstantVariableData &worldData, Camera *camera ) : WorldViewProjData{ worldData, camera } {}

void *SkyBoxWVPData::operator()() const
{
	if ( mData )
	{
		Camera *c			{ static_cast<Camera *>( mData ) };
		XMFLOAT3 camPos		{ c->GetPositionF3() };
		CXMMATRIX T			{ XMMatrixTranslation( camPos.x, camPos.y, camPos.z ) };
		CXMMATRIX viewProj	{ c->GetViewProj() };
		XMStoreFloat4x4( &xmWorldViewProj, XMMatrixTranspose( T * viewProj ) );
		return &xmWorldViewProj;
	}
	else
	{
		return &xmWorld;
	}
}