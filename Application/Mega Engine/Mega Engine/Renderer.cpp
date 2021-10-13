#include "Renderer.h"

#include <sstream>

#include "DebugConsole.h"
#include "Direct3D.h"
#include "GameMaster.h"
#include "JsonScene.h"
#include "Renderable.h"
#include "VertexBuffer.h"

class PipelineState;

using std::stringstream;
using std::showpos;
using console::PrintAt;
using console::Print;

void renderer::Init()
{
	// load scene from file
	JsonScene scene{ "../../../Shared/Json Scenes/Start01.json" };
	
	// parse game objects from json file
	vector<Camera *>		parsedCameras			= scene.ParseCameras();
	vector<PipelineState *> parsedPipelineStates	= scene.ParsePipelineStates();
	vector<Renderable *>	parsedRenderables		= scene.ParseRenderables();

	// cameras
	gm::camera::Set( parsedCameras );

	// pipelines
	gm::pps::Set( parsedPipelineStates );
	gm::pps::AttachAll();

	// renderables
	gm::renderable::Set( parsedRenderables );
	gm::renderable::SetCameraAll();
	gm::renderable::SetPpsAll();

	gm::renderable::OrderAll();
	
	// init vertex/index buffer

	// get shape filenames from renderables
	vector<string> shapeFilenames;
	for ( auto &r : parsedRenderables )
	{
		// check if filename has already been read from a previous renderable
		bool repeat = false;
		for ( auto &filename : shapeFilenames )
		{
			if ( r->GetDesc().shape == filename )
			{
				repeat = true;
				break;
			}
		}

		// if not a repeat, add to filename list
		if (!repeat)
		{
			shapeFilenames.push_back( r->GetDesc().shape );
		}
	}

	vb::Init( shapeFilenames );
}

void UpdateKeyState(float dt)
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float spd = 5.0f * dt;
	if (GetAsyncKeyState('W') & 0x8000)	z += spd; 
	if (GetAsyncKeyState('S') & 0x8000)	z -= spd; 
	if (GetAsyncKeyState('A') & 0x8000)	x -= spd; 
	if (GetAsyncKeyState('D') & 0x8000)	x += spd; 
	if (GetAsyncKeyState('R') & 0x8000)	y += spd;
	if (GetAsyncKeyState('F') & 0x8000)	y -= spd;

	gm::camera::Move( "mainCam", x, y, z );
}

void renderer::Update(float dt)
{
	UpdateKeyState(dt);

	// update camera
	gm::camera::Update();

	// FPS and SPF

	static UINT frameCount = 0;
	frameCount++;

	static float accDt = 0.0f;
	accDt += dt;

	if (accDt > 1.0f)
	{
		float avgDt = accDt / (float)frameCount;

		stringstream ss;
		ss << "Seconds Per Frame: " << avgDt << "\t\t\n";		// tabs are there to ensure clearing of previous contents
		ss << "Frames Per Second: " << frameCount << "\t\t\n";

		PrintAt(ss.str(), 0, 0, console::CYAN);

		accDt = 0.0f;
		frameCount = 0;
	}
}

void renderer::Render()
{
	// clear all render targets and screen
	gm::pps::ClearAll();

	// render scene
	gm::renderable::RenderAll();

	d3d::GetSwapChain()->Present(0, 0);
}

void renderer::Unin()
{
	gm::Unin();
}

int lastMousePosX = 0;
int lastMousePosY = 0;

void renderer::OnMouseDown(WPARAM btnState, int x, int y)
{
	lastMousePosX = x;
	lastMousePosY = y;
}

void renderer::OnMouseUp(WPARAM btnState, int x, int y)
{
	// do stuff here
}

void renderer::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0) 
	{
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - lastMousePosX));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - lastMousePosY));

		gm::camera::Turn( "mainCam", dy, dx );
	}

	lastMousePosX = x;
	lastMousePosY = y;
}

static const char *const shapes[] {
	"../../../Shared/Models/suzanne.3ds", 
	"../../../Shared/Models/cube.obj", 
	"../../../Shared/Models/torus.3ds",
	"../../../Shared/Models/sphere.3ds"
};

void renderer::OnKeyDown(WPARAM key)
{
	static int i = 0;
	if ( GetAsyncKeyState( VK_SPACE ) )
	{
		auto renderables = gm::renderable::Get();

		for ( auto &r : renderables )
		{
			auto &rd = r->GetDesc();
			if ( rd.pipelineState == "EnvMapLookupPPS" )
			{
				rd.shape = shapes[i++];

				if ( i > 3 )
					i = 0;
			}
		}
	}
}

void renderer::OnKeyUp(WPARAM key)
{
	// do stuff here...
}