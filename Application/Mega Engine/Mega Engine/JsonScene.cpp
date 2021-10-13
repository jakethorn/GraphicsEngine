#include "JsonScene.h"

#include "Camera.h"
#include "DebugConsole.h"
#include "Direct3D.h"
#include "Factory.h"
#include "InputLayout.h"
#include "JsonUtil.h"
#include "Renderable.h"
#include "WinMain.h"
#include "RenderTarget.h"
#include "UnstructuredFunctions.h"
#include "JsonKeywords.h"
#include "ConstantVariableDataFactory.h"

using std::string;

////////////////////
// constructor

JsonScene::JsonScene( string filename )
{
	ParseIncludes( filename );
}

JsonScene::~JsonScene()
{
	for ( auto &d : mDocuments )
		delete d;
}

////////////////////
// parse includes

void JsonScene::ParseIncludes( const string &filename )
{
	// open new json document
	Document *tmp = new Document;
	json::Open( filename, *tmp );

	// add to open documents
	mDocuments.push_back( tmp );
	
	// return, if the document doesn't include files
	if ( !tmp->HasMember( json::keyword::Include ) )
		return;

	// add all included files
	for ( unsigned int i = 0; i < ( *tmp )[json::keyword::Include].Size(); ++i )
	{
		ParseIncludes( ( *tmp )[json::keyword::Include][i].GetString() );	// Recursion
	}
}

////////////////////
// find values

vector<const Value *const> JsonScene::FindValues(const string &s) const
{
	vector<const Value *const> retval;

	// for all open documents, find all values with objects matching s
	for ( auto & d : mDocuments )
		if ( d->HasMember( s.c_str() ) )
			retval.push_back( &(*d)[s.c_str()] );

	return retval;
}

////////////////////
// parse cameras

vector<Camera *> JsonScene::ParseCameras() const
{
	// find all cameras
	auto v = FindValues( json::keyword::CameraArray );

	vector<Camera *> parsedCameras;

	// parse all cameras and add them to vector
	for ( unsigned int i = 0; i < v.size(); ++i )
		for ( unsigned int j = 0; j < v[i]->Size(); ++j )
			parsedCameras.push_back( ParseCamera( (*v[i])[j] ) );

	return parsedCameras;
}

////////////////////
// parse camera

Camera* JsonScene::ParseCamera( const Value & v ) const
{
	// get camera info
	string			name	= json::GetString		( v, "name" );
	vector<float>	pos		= json::GetFloatVector	( v, "position" );
	vector<float>	look	= json::GetFloatVector	( v, "look" );
	float			fov		= json::GetFloat		( v, "fov" );
	bool			ortho	= json::GetBool			( v, "ortho" );

	// create new camera
	Camera *camera = new Camera{ name };

	// set camera position and orientation
	camera->SetPositionF3( { &pos[0] } );
	camera->LookAtF3( { &look[0] } );

	// set camera frustum
	if ( ortho )	camera->SetOrthoFrustum( -150.0f, 150.0f, -150.0f, 150.0f, 0.0f, 400.0f );
	else			camera->SetFrustum( fov * XM_PI, (float)GetWindowWidth() / GetWindowHeight(), 0.1f, 1000.0f );

	return camera;
}

////////////////////
// parse pipeline state

vector<PipelineState *> JsonScene::ParsePipelineStates() const
{
	// find all pipeline states
	auto v = FindValues( json::keyword::PipelineStateArray );

	vector<PipelineState *> parsedPipelineStates;
	
	// parse all pipeline states and add them to vector
	for ( unsigned int i = 0; i < v.size(); ++i )
		for ( unsigned int j = 0; j < v[i]->Size(); ++j )
			parsedPipelineStates.push_back( ParsePipelineState( (*v[i])[j] ) );

	return parsedPipelineStates;
}

////////////////////
// parse renderables

vector<Renderable *> JsonScene::ParseRenderables() const
{
	// find all renderables
	auto v = FindValues( json::keyword::RenderableArray );

	vector<Renderable *> parsedRenderables;

	int numRenderableArrays = v.size();
	// parse all renderables and add them to vector
	for ( unsigned int i = 0; i < numRenderableArrays; ++i )
	{
		int renderableArraySize = v[i]->Size();
		for ( unsigned int j = 0; j < renderableArraySize; ++j )
		{
			Renderable *tmp = ParseRenderable( ( *v[i] )[j] );
			parsedRenderables.push_back( tmp );
			
			// cache current renderables description
			auto rd = tmp->GetDesc();

			// add extra reflected renderable if required
			if ( rd.reflectEnabled )
				parsedRenderables.push_back( ParseRenderable( ( *v[i] )[j], rd.reflectPPS, rd.reflectCam, rd.shape, rd.layer ) );

			// add extra shadow renderable if required
			if ( rd.shadowEnabled )
				parsedRenderables.push_back( ParseRenderable( ( *v[i] )[j], rd.shadowPPS, rd.shadowCam, rd.shape, rd.layer - 1 ) );
		}
	}

	return parsedRenderables;
}

////////////////////
// parse pipeline state

PipelineState *JsonScene::ParsePipelineState( const Value & v ) const
{
	/*
		Get Json Values
	*/

	string name					{ json::GetString( v, "name" ) };
	string vsFile				{ json::GetString( v, "shaderFile" ) };
	string hsFile				{ json::GetString( v, "hullShader" ) };
	string dsFile				{ json::GetString( v, "domainShader" ) };
	string gsFile				{ json::GetString( v, "gs_shaderFile" ) };
	string psFile				{ json::GetString( v, "ps_shaderFile" ) };
	vector<string> inputLayout	{ json::GetStringVector( v, "inputLayout" ) };
	const Value & renderTarget	{ json::GetValue( v, "renderTarget" ) };
	string sampler				{ json::GetString( v, "sampler" ) };
	string blend				{ json::GetString( v, "blendState" ) };
	string depthStencil			{ json::GetString( v, "depthStencilState" ) };
	string rasterizer			{ json::GetString( v, "rasterizerState" ) };

	/*
		Create Pipeline State Description
	*/

	PIPELINE_STATE_DESC psd;

	psd.name = name;

	const Value& attachObj = json::GetValue( v, "attach" );
	if ( &attachObj != &v )
	{
		psd.attachTo	= json::GetString( attachObj, "to" );
		psd.numViews	= json::GetInt( attachObj, "numViews" );
		psd.attachDepth = json::GetBool( attachObj, "depth" );
	}

	/*
		Create Shader Stages
	*/

	VertexShaderStage	*vss = new VertexShaderStage	{ vsFile, inputlayout::CreateFromString( inputLayout ) };
	HullShaderStage		*hss = new HullShaderStage		{ hsFile };
	DomainShaderStage	*dss = new DomainShaderStage	{ dsFile };
	GeometryShaderStage *gss = new GeometryShaderStage	{ gsFile };
	PixelShaderStage	*pss = new PixelShaderStage		{ psFile };
	
	// pixel shader sampler
	if		( sampler == "linear" )	pss->SetSampler( factory::CreateLinearSampler() );
	else if ( sampler == "point" )	pss->SetSampler( factory::CreatePointSampler() );

	/*
		Create Other Stages
	*/

	ID3D11BlendState *bs = nullptr;
	if		( blend == "additive" )		bs = factory::CreateAdditiveBlendState();
	else if ( blend == "specialA" )		bs = factory::CreateSpecialisedBlendStateA();

	ID3D11DepthStencilState *ds = nullptr;
	if ( depthStencil == "disabled" )	ds = factory::CreateDisabledDepthStencilState();	
	else								ds = factory::CreateEnabledDepthStencilState();	

	ID3D11RasterizerState *rs = nullptr;
	if ( rasterizer == "noCull" )		rs = factory::CreateNoCullRasterizerState();

	/*
		Create Pipeline State
	*/

	PipelineState *ps = new PipelineState{ 
		vss, hss, dss, gss, pss,
		bs, 
		ds, 
		rs, 
		(renderTarget == v) ? nullptr : ParseRenderTarget( renderTarget ), 
		psd
	};

	// primitive topology
	if ( hsFile != "" )
		ps->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST );

	return ps;
}

////////////////////
// parse render target

RenderTarget * JsonScene::ParseRenderTarget( const Value & v ) const 
{
	int width				{ json::GetInt( v, "width" ) };				// rtv width
	int height				{ json::GetInt( v, "height" ) };			// rtv height
	vector<string> formats	{ json::GetStringVector( v, "formats" ) };	// rtv format
	int slices				{ json::GetInt( v, "slices" ) };			// rtv slices

	// disease means there was no value, only 1 slice
	slices = slices == 0xD15EA5E ? 1 : slices;

	// evaluate width and height
	width = width > 0 ? width : GetWindowWidth();
	height = height > 0 ? height : GetWindowHeight();

	// evaulate real formats
	vector<DXGI_FORMAT> realFormats( formats.size() );
	for (int i = 0; i < formats.size(); i++)
	{
		if		(formats[i] == "R32G32B32A32_FLOAT")	realFormats[i] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		else if (formats[i] == "R8G8B8A8_SNORM")		realFormats[i] = DXGI_FORMAT_R8G8B8A8_SNORM;
		else if (formats[i] == "R8G8B8A8_UNORM")		realFormats[i] = DXGI_FORMAT_R8G8B8A8_UNORM;
		else											realFormats[i] = DXGI_FORMAT_UNKNOWN;

	}

	// temporary cpu access
	const DXGI_FORMAT scump_formats[] {DXGI_FORMAT_UNKNOWN};

	return new RenderTarget{ 
		realFormats.size(), 
		(unsigned)slices,
		(unsigned)width, 
		(unsigned)height, 
		realFormats.size() > 0 ? &realFormats[0] : scump_formats
	};
}

void f(const Value &v, const string &s, const void * const d, const size_t sz, ConstantBufferData &cb)
{
	if ( v.HasMember( s.c_str() ) )
	{
		cb[s] = new IConstantVariableData( d, sz );
	}
}

Renderable *JsonScene::ParseRenderable( const Value &v ) const
{
	return ParseRenderable( 
		v, 
		json::GetString	( v, "pipelineState" ), 
		json::GetString	( v, "camera" ), 
		json::GetString	( v, "shape" ), 
		json::GetInt	( v, "layer" ) 
	);
}

Renderable *JsonScene::ParseRenderable( const Value &v, const string &pipelineState, const string &camera, const string &shape, int layer ) const
{
	ConstantBufferData	cb;
	RENDERABLE_DESC		rd;
	
	/*
		Constant Buffer Setup
	*/

	cb["gWorld"] = ConstantVariableDataFactory::CreateWorldMatrix
	(
		json::GetString			( v, "movementScript" ),
		&json::GetFloatVector	( v, "position" )[0],
		&json::GetFloatVector	( v, "scale"	)[0],
		&json::GetFloatVector	( v, "rotation" )[0]
	);

	cb["gWorldView"]		= ConstantVariableDataFactory::CreateWorldViewMatrix();
	cb["gWorldInvTrn"]		= ConstantVariableDataFactory::CreateWorldInverseTransposeMatrix();
	cb["gWorldViewProj"]	= ConstantVariableDataFactory::CreateWorldViewProjMatrix( json::GetBool( v, "followPlayer" ) );
	cb["gParaboloidBasis"]	= ConstantVariableDataFactory::CreateViewMatrix();
	cb["gViewProj"]			= ConstantVariableDataFactory::CreateViewProjMatrix();
	cb["gShadowTex"]		= ConstantVariableDataFactory::CreateShadowTextureMatrix();
	cb["gCameraPos"]		= ConstantVariableDataFactory::CreateCameraPosition();
	cb["gColour"]			= ConstantVariableDataFactory::Create( json::GetFloatVector( v, "colour" ) );
	cb["gLightColour"]		= ConstantVariableDataFactory::Create( json::GetFloatVector( v, "lightColour" ) );
	cb["gLightPos"]			= ConstantVariableDataFactory::Create( json::GetFloatVector( v, "lightPos" ) );
	cb["gSpecPwr"]			= ConstantVariableDataFactory::Create( json::GetFloat( v, "gSpecPwr" ) );
	cb["gSpecEms"]			= ConstantVariableDataFactory::Create( json::GetFloat( v, "gSpecEms" ) );
	
	/*
		Renderable Description Setup
	*/

	// general desc
	rd.pipelineState	= pipelineState;
	rd.camera			= camera;
	rd.shape			= shape;
	rd.layer			= layer;

	// shadow desc
	const Value& shadowObj = json::GetValue( v, "shadow" );
	if ( &shadowObj != &v )
	{
		rd.shadowEnabled	= json::GetBool		( shadowObj, "enabled"			);
		rd.shadowPPS		= json::GetString	( shadowObj, "pipelineState"	);
		rd.shadowCam		= json::GetString	( shadowObj, "camera"			);
		rd.shadowBias		= json::GetFloat	( shadowObj, "bias"				);
	}

	// reflect desc
	const Value& reflectObj = json::GetValue( v, "reflection" );
	if ( &reflectObj != &v )
	{
		rd.reflectEnabled	= json::GetBool		( reflectObj, "enabled"			);
		rd.reflectPPS		= json::GetString	( reflectObj, "pipelineState"	);
		rd.reflectCam		= json::GetString	( reflectObj, "camera"			);
	}

	// reflector desc
	rd.reflectorCam	= json::GetString( v, "isReflector" );

	/*
		Create Renderable
	*/

	Renderable *retval = new Renderable{ nullptr, cb, rd };

	/*
		Renderable Setters
	*/

	if ( v.HasMember( "resourceSlot" ) )
		retval->SetPrimaryPSShaderResourceSlot( v["resourceSlot"].GetInt() );

	if ( v.HasMember( "texture" ) )
	{
		std::wstring texdir = help::ToWString( json::GetString( v, "texture" ) );

		ID3D11ShaderResourceView* srv;
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile( d3d::GetDevice(), texdir.c_str(), 0, 0, &srv, 0 );
		console::Print( hr, "CreateShaderResourceViewFromFile" );

		retval->SetSRV( srv );
	}
		
	return retval;
}