#include "ViewData.h"

#include "Camera.h"

ViewData::ViewData(Camera *data) : IConstantVariableData{ data }
{

}

void *ViewData::operator()() const
{
	if ( mData )
	{
		CXMMATRIX view{ static_cast<Camera *>( mData )->GetView() };
		XMStoreFloat4x4( &xmView, XMMatrixTranspose( view ) );
	}
	
	return &xmView;
}