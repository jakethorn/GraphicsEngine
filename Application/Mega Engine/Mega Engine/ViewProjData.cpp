#include "ViewProjData.h"

#include "Camera.h"

ViewProjData::ViewProjData(Camera *data) : IConstantVariableData{ data }
{

}

void *ViewProjData::operator()() const
{
	if ( mData )
	{
		CXMMATRIX viewProj{ static_cast<Camera *>( mData )->GetViewProj() };
		XMStoreFloat4x4( &xmViewProj, XMMatrixTranspose( viewProj ) );
	}
	
	return &xmViewProj;
}