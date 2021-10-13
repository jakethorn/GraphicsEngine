#include "ConstantVariableDataFactory.h"

#include "CameraPositionData.h"
#include "Common.h"
#include "OscillateWorldData.h"
#include "RotateWorldData.h"
#include "ShadowTexData.h"
#include "SkyBoxWVPData.h"
#include "ViewData.h"
#include "ViewProjData.h"
#include "WorldInverseTransposeData.h"
#include "WorldViewData.h"
#include "WorldViewProjData.h"

#include <d3d11.h>
#include <xnamath.h>

IConstantVariableData *ConstantVariableDataFactory::mCachedWorldMatrix = nullptr;

IConstantVariableData *ConstantVariableDataFactory::CreateWorldMatrix( string movementType, const float *const pPosition, const float *const pScale, const float *const pRotation )
{
	// convert scale, rotation and position
	CXMVECTOR scale		= XMVectorSet( pScale[0],		pScale[1],		pScale[2],		1.0f );
	CXMVECTOR rotation	= XMVectorSet( pRotation[0],	pRotation[1],	pRotation[2],	1.0f );
	CXMVECTOR position	= XMVectorSet( pPosition[0],	pPosition[1],	pPosition[2],	1.0f );

	// create world matrix
	XMMATRIX world{ XMMatrixIdentity() };
	world *= XMMatrixScalingFromVector( scale );
	world *= XMMatrixRotationRollPitchYawFromVector( rotation );
	world *= XMMatrixTranslationFromVector( position );
	world = XMMatrixTranspose( world );

	// create data depending on movement type
	if		( movementType == "rotate" )	mCachedWorldMatrix = new RotateWorldData		{ &world };
	else if ( movementType == "oscillate" )	mCachedWorldMatrix = new OscillateWorldData		{ &world };
	else									mCachedWorldMatrix = new IConstantVariableData	{ &world, sizeof( world ) };

	return mCachedWorldMatrix;
}

IConstantVariableData *ConstantVariableDataFactory::CreateWorldInverseTransposeMatrix()
{
	return new WorldInverseTransposeData{ *mCachedWorldMatrix };
}

IConstantVariableData *ConstantVariableDataFactory::CreateWorldViewMatrix()
{
	return new WorldViewData{ *mCachedWorldMatrix, nullptr };
}

IConstantVariableData *ConstantVariableDataFactory::CreateWorldViewProjMatrix( bool shouldFollowPlayer )
{
	return shouldFollowPlayer ? new SkyBoxWVPData{ *mCachedWorldMatrix, nullptr } : new WorldViewProjData{ *mCachedWorldMatrix, nullptr };
}

IConstantVariableData *ConstantVariableDataFactory::CreateViewMatrix()
{
	return new ViewData{ nullptr };
}

IConstantVariableData *ConstantVariableDataFactory::CreateViewProjMatrix()
{
	return new ViewProjData{ nullptr };
}

IConstantVariableData *ConstantVariableDataFactory::CreateCameraPosition()
{
	return new CameraPositionData{ nullptr };
}

IConstantVariableData *ConstantVariableDataFactory::CreateShadowTextureMatrix()
{
	return new ShadowTexData{ *mCachedWorldMatrix, nullptr };
}