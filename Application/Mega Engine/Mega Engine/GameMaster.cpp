#include "GameMaster.h"

#include <algorithm>

#include "Camera.h"
#include "PipelineState.h"
#include "Renderable.h"

////////////////////
// Static Variables

vector<Camera *> sCameras;			// Cameras.
vector<PipelineState *> sPpss;		// Pipeline states.
vector<Renderable *> sRenderables;	// Renderables.

void gm::Unin()
{
	for ( auto &cam : sCameras )
		delete cam;

	for ( auto &pps : sPpss )
		delete pps;

	for ( auto &rndr : sRenderables )
		delete rndr;
}

////////////////////
// Set Camera

void gm::camera::Set( const vector<Camera *> &c )
{
	sCameras = c;
}

////////////////////
// Move Camera

void gm::camera::Move( string camName, float x, float y, float z )
{
	Camera* cam = nullptr;

	for ( auto& a : sCameras )
		if ( a->GetDesc().name == camName )
			cam = a;

	if ( !cam )
		return;

	cam->TranslateX( x );
	cam->TranslateWorldY( y );
	cam->TranslateZ( z );
}

////////////////////
// Turn Camera

void gm::camera::Turn( string camName, float x, float y )
{
	Camera* cam = nullptr;

	for ( auto& a : sCameras )
		if ( a->GetDesc().name == camName )
			cam = a;

	if ( !cam )
		return;

	cam->RotateX( x );
	cam->RotateY( y );
}

////////////////////
// Update Camera

void gm::camera::Update()
{
	for ( auto& a : sCameras )
		a->Update();
}

////////////////////
// Set Pipeline States

void gm::pps::Set( const vector<PipelineState *> &ppss )
{
	sPpss = ppss;	
}

////////////////////
// Attach All Pipeline States

void gm::pps::AttachAll()
{
	for ( auto &a : sPpss )
	{
		for ( auto &b : sPpss )
		{
			if ( a->GetDesc().attachTo == b->GetDesc().name )
			{
				a->SetShaderResources( PIXEL_STAGE, 0, a->GetDesc().numViews, b->GetResult() );	// Attach result of PPS B to resource view of PPS A
				if ( a->GetDesc().attachDepth )
				{
					a->SetShaderResources( PIXEL_STAGE, a->GetDesc().numViews, 1, b->GetDepth() );
				}
			}
		}
	}
}

////////////////////
// Clear All Pipeline States

void gm::pps::ClearAll()
{
	for ( auto &a : sPpss )
		a->Clear();
}

////////////////////
// Set Active Pipeline State

void gm::pps::SetActive( const PipelineState * const newActivePps )
{
	for ( auto &a : sPpss )
		a->SetIsActive( a == newActivePps );
}

////////////////////
// Set Renderables

void gm::renderable::Set( const vector<Renderable *> &rndrs )
{
	sRenderables = rndrs;
}

////////////////////
// Set All Renderables Camera To Custom Camera

void gm::renderable::SetCameraAll( Camera * const c )
{
	for ( auto &a : sRenderables )
	{
		if ( a->GetDesc().camera == c->GetDesc().name )
			a->SetCamera( c );
		else
			a->SetCamera( nullptr );
	}
}

////////////////////
// Set All Renderables Camera To Default

void gm::renderable::SetCameraAll()
{
	for ( auto &a : sRenderables )
		for ( auto &b : sCameras )
			if ( a->GetDesc().camera == b->GetDesc().name )
				a->SetCamera( b );
	
	// shadow cameras
	
	for ( auto &a : sRenderables )
		for ( auto &b : sCameras )
			if ( a->GetDesc().shadowCam == b->GetDesc().name )
				a->SetShadowCamera( b );

	// reflector cameras
	
	for ( auto &a : sRenderables )
		for ( auto &b : sCameras )
			if ( a->GetDesc().reflectorCam == b->GetDesc().name )
				a->SetReflectorCamera( b );
}

////////////////////
// Set All Renderables Pipeline State To Custom Pipeline State

void gm::renderable::SetPpsAll( const vector<PipelineState *> &ppsd )
{
	for ( auto &a : sRenderables )
		for ( auto &b : ppsd )
			if ( a->GetDesc().pipelineState == b->GetDesc().name )
				a->SetPipelineState( b );
}

////////////////////
// Set All Renderables Pipeline State To Default

void gm::renderable::SetPpsAll()
{
	SetPpsAll( sPpss );
}

////////////////////
// Order All Renderables

void gm::renderable::OrderAll()
{
	std::sort( sRenderables.begin(), sRenderables.end(),
			   [] ( const Renderable * const a, const Renderable * const b ) -> bool
				{ 
					return a->GetDesc().layer < b->GetDesc().layer; 
				}
	);
}

////////////////////
// Render All Renderables

void gm::renderable::RenderAll()
{
	for ( auto &a : sRenderables )
		a->Draw();
}

vector<Renderable *> &gm::renderable::Get()
{
	return sRenderables;
}